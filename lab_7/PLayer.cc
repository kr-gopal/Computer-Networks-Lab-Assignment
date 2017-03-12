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

#include "PLayer.h"
#include "R_PDU_m.h"
Define_Module(PLayer);

void PLayer::initialize()
{
    // TODO - Generated method body
   Fnode=gate("Fnode");
  Fdl=gate("Fdl");
  Tnode=gate("Tnode");
  Tdl=gate("Tdl");
}
void PLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(uniform(0,1)>1)
    {
        bubble("MESSAGE LOST!");
        delete msg;
    }
    else
    {
        if(msg->getArrivalGate()==Fdl)
        {
            if(strcmp(msg->getClassName(),"R_PDU")==0)
            {

                R_PDU *rpdu=check_and_cast<R_PDU*>(msg);
                send(rpdu,Tnode);
            }
            else
            {
                DL_PDU *dpdu=check_and_cast<DL_PDU*>(msg);
                P_PDU *pdu=new P_PDU();
                pdu->setType(dpdu->getType());
                pdu->encapsulate(dpdu);
                send(pdu,Tnode);
            }
        }
        else if(msg->getArrivalGate()==Fnode)
        {
            if(strcmp(msg->getClassName(),"R_PDU")==0)
            {
                R_PDU *rpdu=check_and_cast<R_PDU*>(msg);
                send(rpdu,Tdl);
            }
            else
            {
                EV<<"AYA TO THA";
                P_PDU* ppdu=check_and_cast<P_PDU*>(msg);
                send(ppdu->decapsulate(),Tdl);
            }
        }
    }
}
