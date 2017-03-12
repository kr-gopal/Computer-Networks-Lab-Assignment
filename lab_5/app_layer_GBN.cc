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

#include "app_layer_GBN.h"
#include "AL_PKT_m.h"
#include "DLL_PKT_m.h"

Define_Module(App_layer_GBN);

void App_layer_GBN::initialize()
{
    // TODO - Generated method body
    AppLId = par("AppLId");
    count = 0;
    WATCH(count);
    gDLOut = gate("gDLOut");
    gDLIn = gate("gDLIn");
    if(AppLId == 1){
        cMessage* msg = new cMessage("Self Message");
        scheduleAt(0,msg);
    }
}

void App_layer_GBN::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if( AppLId == 1){
        if(msg->isSelfMessage()){
            AL_PKT* pkt = getNewAppPkt();
            bubble("Sending Packet.");
            send(pkt,gDLOut);
            count++;
            if(count <= 25){
                cMessage* msg = new cMessage("Self Message");
                scheduleAt(simTime(),msg);
            }
        }
        else
            delete msg;
    }
    else if(AppLId == 2){
        if(msg->getArrivalGate() == gDLIn){
            DLL_PKT* pkt = check_and_cast<DLL_PKT*>(msg);
            AL_PKT* alPkt = check_and_cast<AL_PKT*>(pkt->decapsulate());
            AL_PKT* nPkt = getAckAppPkt(alPkt->getId());
            send(nPkt,gDLOut);
        }
        else
            delete msg;
    }
    else
        delete msg;
}

AL_PKT* App_layer_GBN::getNewAppPkt(){
    AL_PKT* pkt = new AL_PKT();
    pkt->setId(count);
    pkt->setType(0);
    pkt->setName("Packet");
    return pkt;
}

AL_PKT* App_layer_GBN::getAckAppPkt(int id){
    AL_PKT* pkt = new AL_PKT();
    pkt->setId(id);
    pkt->setType(1);
    pkt->setName("Acknowledgment");
    return pkt;
}
