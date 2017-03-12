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

#include "ALayer.h"
#include "A_PDU_m.h"
#include "Ack_m.h"
#include "Data_m.h"
Define_Module(ALayer);
void ALayer::initialize()
{
    // TODO - Generated method body
    id=par("id");
    in=gate("Fnw");
    out=gate("Tnw");
    cnt=0;
    noOfPackets=par("numPackets");
    src=par("src");
    dest=par("dest");
    if(id==src)
    {
        EV<<"I AM HERE\n";
        delay =2.0;
        cMessage *msg=new cMessage("event");
        scheduleAt(100,msg);
    }
}

void ALayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->isSelfMessage())
    {
        EV<<"SHURU HO GYA!";
        cnt++;
        Data *data=new Data();
        data->setSrc(src);
        data->setDest(dest);
        if(data->getSrc()!=data->getDest())
        {
            A_PDU *apdu=new A_PDU();
            apdu->setSrc(data->getSrc());
            apdu->setDest(data->getDest());
            apdu->setId(cnt);
            apdu->setType('D');
            apdu->encapsulate(data);
            sendDelayed(apdu,delay,out);
        }
    }
    else if(msg->getArrivalGate()==in)
    {
        A_PDU *apdu=check_and_cast<A_PDU*>(msg);
    //    EV<<apdu->getType()<<endl;
        if(apdu->getType()=='A')
        {
            EV<<"AAYA BHI HAIN KYA?";
            if(cnt==noOfPackets)
            {
                EV<<"ABE RUKA KYON NAHI!";
                delete msg;
            }
            else
            {
            //    EV<<"Sending Data\n";
                cnt++;
                EV<<cnt<<endl;
                Data *data=new Data();
                data->setSrc(apdu->getDest());
                data->setDest(apdu->getSrc());
                A_PDU* apdu1=new A_PDU();
                apdu1->encapsulate(data);
                apdu1->setType('D');
                apdu1->setSrc(data->getSrc());
                apdu1->setDest(data->getDest());
                apdu1->setId(cnt);
                sendDelayed(apdu1,delay,out);
            }
        }
        else
        {
            receiverTime=simTime();
            propagationDelay=receiverTime-(apdu->getSenderTime());
            propagationDelayVector.record(propagationDelay);
            propagationDelayStats.collect(propagationDelay);
           // EV<<"Propogation delay for packet "<<apdu->getId()<<" is "<<propagationDelay<<endl;
           // EV<<"Sending Ack\n";
            Ack *ack=new Ack();
            A_PDU *apdu1=new A_PDU();
            apdu1->encapsulate(ack);
            apdu1->setSrc(apdu->getDest());
            apdu1->setDest(apdu->getSrc());
            apdu1->setType('A');
            send(apdu1,out);
        }
    }
}
