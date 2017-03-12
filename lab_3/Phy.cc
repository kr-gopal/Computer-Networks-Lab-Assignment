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

#include "Phy.h"
#include "P_PDU_m.h"

Define_Module(Physical);

void Physical::initialize()
{
    gIn1 = gate("gin1");
       gIn2 = gate("gin2");
       gOut1 = gate("gout1");
       gOut2 = gate("gout2");
       node_id=par("node_id");
       //P_PDU* m = new P_PDU();

}

void Physical::handleMessage(cMessage *msg)
{

    if (msg->getArrivalGate() == gIn1)
    {
            P_PDU* messagePL = new P_PDU();

            messagePL->encapsulate(check_and_cast<cPacket*>(msg));
            send(messagePL, gOut2);
     }
    else
    {
            cPacket* p = check_and_cast<cPacket*>(msg);
            send(p->decapsulate(), gOut1);

            if(node_id==1)
            {
                if (uniform(0,1) < 0.4)
                {
                    EV << "\"Losing\" message.\n";
                    bubble("message lost");  // making animation more informative...
                    delete msg;
                }
            }
            else if(node_id==2)
            {
                if (uniform(0,1) < 0.55)
                {
                    EV << "\"Losing\" message.\n";
                    bubble("message lost");  // making animation more informative...
                    delete msg;
                }
            }
    }
}
