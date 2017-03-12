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

#include "Alayer.h"
#include "alpdu_m.h"

Define_Module(Alayer);

void Alayer::initialize()
{
    id=par("id");
    if(id==1)
    {
      cMessage* msg=new cMessage();
      scheduleAt(0,msg);
    }
}

void Alayer::handleMessage(cMessage *msg)
{
   static int count=0;
    if(msg->isSelfMessage())
    {
        A_PDU* pkt=new A_PDU();
        pkt->setId(0);
        pkt->setType(0);
        send(pkt,gate("goutdown"));
    }
    else
    {
        if(count==1)
                   delete msg;
        else {
                   A_PDU* pkt = check_and_cast<A_PDU*> (msg);

                   if(pkt->getType()==0)
                   {
                       count++;
                       pkt->setType(1);
                       pkt->setId(1);
                       send(pkt,gate("goutdown"));
                   }
                  else
                   {
                          pkt->setId(0);
                          pkt->setType(0);
                          send(pkt,gate("goutdown"));
                   }
               }
    }
}
