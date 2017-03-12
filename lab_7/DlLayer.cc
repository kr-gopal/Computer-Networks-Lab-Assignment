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

#include "DlLayer.h"
#include "A_PDU_m.h"
#include "DL_PDU_m.h"
#include "P_PDU_m.h"
#include "N_PDU_m.h"
#include "R_PDU_m.h"
Define_Module(DlLayer);

void DlLayer::initialize()
{
    // TODO - Generated method body
    Fnw=gate("Fnw");
    Fpl=gate("Fpl");
    Tpl=gate("Tpl");
    Tnw=gate("Tnw");
    timeout = 3.0;
    nodeId=par("id");
    timeoutEvent = new cMessage("timeoutEvent");
}

void DlLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg==timeoutEvent)
    {
        send(copy->dup(),Tpl);
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
    else if(msg->getArrivalGate()==Fpl)
    {
        if(strcmp(msg->getClassName(),"R_PDU")==0)
        {
            R_PDU *rpdu=check_and_cast<R_PDU*>(msg);
            send(rpdu,Tnw);
        }
        else
        {
            DL_PDU *dpdu=check_and_cast<DL_PDU*>(msg);
            EV<<dpdu->getType()<<" FPL";
            EV<<nodeId<<" "<<dpdu->getDest()<<endl;
            if(dpdu->getType()=='A')
            {
             // EV<<"Event is being cancelled\n";
              cancelEvent(timeoutEvent);
            }
            send(dpdu->decapsulate(),Tnw);
        }
    }
    else if(msg->getArrivalGate()==Fnw)
    {
        if(strcmp(msg->getClassName(),"R_PDU")==0)
        {
            R_PDU *rpdu=check_and_cast<R_PDU*>(msg);
            send(rpdu,Tpl);
        }
        else
        {
           N_PDU *npdu=check_and_cast<N_PDU*>(msg);
           DL_PDU* dpdu=new DL_PDU();
           dpdu->encapsulate(npdu);
           dpdu->setSrc(npdu->getSrc());
           dpdu->setDest(npdu->getDest());
           dpdu->setType(npdu->getType());
           if(dpdu->getType()=='D')
           {
               //EV<<nodeId<<" "<<dpdu->getSrc()<<endl;
               if(nodeId==dpdu->getSrc())
               {
                   copy=dpdu->dup();
                 //  EV<<"YAHI DATA YAHI TIMER IS SCHEDULED\n";
                   //cancelEvent(timeoutEvent);
                   scheduleAt(simTime()+timeout, timeoutEvent);
                   send(dpdu->dup(),Tpl);
               }
               else
               {
                   send(dpdu,Tpl);
               }
           }
           else
           {
               send(dpdu,Tpl);
           }
        }
    }
}
