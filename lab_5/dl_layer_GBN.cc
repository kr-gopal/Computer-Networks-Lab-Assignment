//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "dl_layer_GBN.h"
#include "pktHandle_m.h"

using namespace std;

Define_Module(Dl_layer_GBN);

void Dl_layer_GBN::initialize()
{
    // TODO - Generated method body
    DLLId = par("DLLId");
    gAppIn = gate("gAppIn");
    gPhyIn = gate("gPhyIn");
    gAppOut = gate("gAppOut");
    gPhyOut = gate("gPhyOut");
    D_p = par("D_p");
    D_pr = par("D_pr");
    crrPkt = 0;
    pktSent = 0;
    window = par("window");
    if( DLLId == 1){
        pktVector.resize(26);
        timeOutEvent.resize(window);
        sentFrame = 0;
        timeout = 0.405;
        sf = 0;
        sn = 0;
        sl = window;
        WATCH(sf);
        WATCH(sn);
        WATCH(sl);
        handle = new cMessage("Packet Handle");
        for(int i=0;i<window;i++)
            timeOutEvent[i] = new cMessage("timeoutEvent");
    }
    else if(DLLId == 2){
        pktVector.resize(1);
        WATCH(rn);
    }
}

void Dl_layer_GBN::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(DLLId == 1){
        if(opp_strcmp(msg->getName(),"timeoutEvent") == 0 && !handle->isScheduled()){
            crrPkt = 0;
            rn = msg->getKind();
            EV<< " Timeout : " << rn << endl;
            sl = min(rn + window, 26);
            sf = rn;
            sn = rn;
            scheduleAt(simTime(),handle);
        }
        else if(msg == handle){
            AL_PKT* appPkt = check_and_cast<AL_PKT*>(pktVector[sn]->dup());
            DLL_PKT* frame = getNewDataPkt(appPkt);
            EV << "Sending Frame : " << sn << " : " << crrPkt << endl;
            pktSent++;
            if(timeOutEvent[crrPkt]->isScheduled())
            {
                pktSent--;
                cancelEvent(timeOutEvent[crrPkt]);
            }
            timeOutEvent[crrPkt]->setKind(sn);
            pktSent++;
            send(frame,gPhyOut);
            scheduleAt(simTime() + 0.401 + crrPkt*0.001, timeOutEvent[crrPkt]);
            crrPkt = (crrPkt + 1) % window;
            sn = sf + crrPkt;
            if(sn >= sl)
            {
                crrPkt = 0;
                sn = sf;
            }
            if(crrPkt > 0)
            scheduleAt(simTime(),handle);
        }
        else if(msg->getArrivalGate() == gAppIn){
            AL_PKT* appPkt = check_and_cast<AL_PKT*>(msg->dup());
            bubble("Packet Received");
            pktVector[appPkt->getId()] = msg->dup();
            crrPkt = 0;
            if(appPkt->getId() == 0)
                scheduleAt(0.1, handle);
        }
        else if(msg->getArrivalGate() == gPhyIn){
            PL_PKT* phyPkt = check_and_cast<PL_PKT*>(msg);
            rn = phyPkt->getId();
            EV << "Requested Packet : "<< phyPkt->getId() << endl;
            if((sf <= rn-1 && rn-1 < sl) && timeOutEvent[rn-sf-1]->isScheduled())
            {
                DLL_PKT* dllPkt = check_and_cast<DLL_PKT*>(phyPkt->decapsulate());
                initialTime = dllPkt->getArrivalTime();
                roundDelayCountStats.collect(simTime()-initialTime);
                roundDelayCountVector.record(simTime()-initialTime);
                cancelEvent(timeOutEvent[rn-sf-1]);
            }
            if(rn >= sl && rn < 26){
                sl = min(rn + window, 26);
                sf = rn;
                sn = rn;
                crrPkt = 0;
                if(handle->isScheduled())
                cancelEvent(handle);
                scheduleAt(simTime(), handle);
            }
            else
                delete msg;
        }
        else
            delete msg;
        numSent = pktSent;
    }
    else if(DLLId == 2){
        if(msg->getArrivalGate() == gPhyIn){
            PL_PKT* phyPkt = check_and_cast<PL_PKT*>(msg);
            EV << "Packet Id : " << phyPkt->getId() << " Received " << endl;
            maxReceived = maxReceived > phyPkt->getId() ? maxReceived : phyPkt->getId();
            if( rn == phyPkt->getId()){
                bubble("Correct Packet Received");
                numReceived++;
                DLL_PKT* dllPkt = check_and_cast<DLL_PKT*>(phyPkt->decapsulate());
                send(dllPkt,gAppOut);
                rn = rn + 1;
                initialTime = dllPkt->getArrivalTime();
                if(rn <= 26){
                    dllPkt = getDataAckPkt(rn);
                    dllPkt->setArrivalTime(initialTime);
                    send(dllPkt,gPhyOut);
                }
            }
            else if(rn < 26){
                EV << "Unwanted Packet Received." << endl;
                delete msg;
                if(rn > maxReceived){
                    DLL_PKT* dllPkt = getDataAckPkt(rn);
                    send(dllPkt,gPhyOut);
                }
            }
            else
                delete msg;
        }
        else
            delete msg;
    }
    else
        delete msg;
}

DLL_PKT* Dl_layer_GBN::getNewDataPkt(AL_PKT *appPkt){
    DLL_PKT* frame = new DLL_PKT();
    frame->setId(appPkt->getId());
    frame->setName("Packet");
    frame->setType(appPkt->getType());
    frame->encapsulate(appPkt);
    frame->setArrivalTime(simTime());
    return frame;
}

DLL_PKT* Dl_layer_GBN::getDataAckPkt(int id){
    DLL_PKT* frame = new DLL_PKT();
    frame->setId(id);
    frame->setName("Acknowledgment");
    frame->setType(0);
    frame->setArrivalTime(simTime());
    return frame;
}

int Dl_layer_GBN::min(int a,int b){
    return (a < b ? a : b);
}

void Dl_layer_GBN::finish(){
    if(DLLId==1){
        // This function is called by OMNeT++ at the end of the simulation.
        EV << "Sent:     " << numSent << endl;
        EV << "Received: " << numReceived << endl;
        EV << "count, min:    " << roundDelayCountStats.getMin() << endl;
        EV << "count, max:    " << roundDelayCountStats.getMax() << endl;
        EV << "count, mean:   " << roundDelayCountStats.getMean() << endl;
        EV << "count, stddev: " << roundDelayCountStats.getStddev() << endl;

        recordScalar("#sent", numSent);
        recordScalar("#received", numReceived);

        roundDelayCountStats.recordAs("count");
    }
}
