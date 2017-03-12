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

#include "App.h"

Define_Module(Application);
#include "A_PDU_m.h"
#include "DL_PDU_m.h"

void Application::initialize()
{
    gIn = gate("gin");
    gOut = gate("gout");
    node_id=par("node_id");
    msg_count=par("msg_count");
    if(node_id==1)
    {
        cMessage* msg = new A_PDU();
        scheduleAt(simTime()+2,msg);
        timeout = 8.0;
        timeoutEvent = new cMessage("timeoutEvent");
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
}

void Application::handleMessage(cMessage *msg)
{

    if (msg==timeoutEvent)
    {
        // If we receive the timeout event, that means the packet hasn't
        // arrived in time and we have to re-send it.
        EV << "Timeout expired, resending message and restarting timer\n";
        A_PDU *newMsg = new A_PDU("tictocMsg");
        send(newMsg, gOut);
        if(msg_count<10)
            scheduleAt(simTime()+timeout, timeoutEvent);
    }

    else if(msg -> isSelfMessage())
       {  A_PDU* message = check_and_cast<A_PDU*>(msg);
              msg_count++;
              message->setData("Data");
              //message->setId(msg_count);
              send(message, gOut);
       }
    else
    {  A_PDU* message = check_and_cast<A_PDU*>(msg);
       if(msg_count <10)
       {
           if(node_id==1)
           {
               if(msg->getArrivalGate()==gIn )
               {
                   bubble("ack received");
               }
               message->setData("data");
               //message->setId(msg_count);
               if(uniform(0,1) < 0.1)
                   scheduleAt(simTime()+2,message);
               else
                   scheduleAt(simTime()+1,message);

                cancelEvent(timeoutEvent);
                scheduleAt(simTime()+timeout, timeoutEvent);
           }
           else if(node_id==2)
           {
               if(msg->getArrivalGate()==gIn)
               {
                   bubble("message received");
                   //delete message;
               }
           }

       }

    }

}
