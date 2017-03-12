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

#include "Data.h"
#include"DL_PDU_m.h"
#include"A_PDU_m.h"
Define_Module(Datalink);


void Datalink::initialize()
{
    gIn1 = gate("gin1");
    gIn2 = gate("gin2");
    gOut1 = gate("gout1");
    gOut2 = gate("gout2");
    node_id = par("node_id");
    count=par("count");
}

void Datalink::handleMessage(cMessage *msg)
{
if(msg -> isSelfMessage())
       {
        A_PDU* messageA=new A_PDU();
        DL_PDU* messageDL=new DL_PDU();
        messageDL->setData("ACK");
        messageDL->setId((count+1)%2);
        count++;
        messageDL->encapsulate(check_and_cast<A_PDU*>(messageA));
        send(messageDL,gOut2);
       }
    else if (msg->getArrivalGate() == gIn1)
    {
        DL_PDU* messageDL = new DL_PDU();
        messageDL->encapsulate(check_and_cast<cPacket*>(msg));
        messageDL->setId(count % 2);
        count++;
        send(messageDL, gOut2);
    }
    else if(msg->getArrivalGate()==gIn2)
    {
        cPacket* p = check_and_cast<cPacket*>(msg);
        send(p->decapsulate(), gOut1);
        if(node_id==2)
        {
            cMessage *m=new cMessage();
            if(uniform(0,1) < 0.4)
                scheduleAt(simTime()+2,m);
            else
                scheduleAt(simTime()+1,m);

        }
    }
}

