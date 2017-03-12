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

#include "node.h"
#include "packet_m.h"
#include "ack_m.h"

Define_Module(Node);

void Node::initialize()
{
   id=par("nodeid");
   in=gate("gin");
   out=gate("gout");
   if(id==1)
      {
          cMessage* msg=new cMessage("event");
          scheduleAt(0,msg);
      }
}

void Node::handleMessage(cMessage *msg)
{
    static int count=0;

    if(msg->isSelfMessage())
    {

        mypkt* pkt=new mypkt();
        pkt->setId(0);
        pkt->setType(0);
        send(pkt,out);
    }
    else
    {

        count++;
        if(count==5)
            delete msg;
        else {
            mypkt * pkt = check_and_cast<mypkt*> (msg);
            if(pkt->getType()==0)
            {
                Ack* pkt=new Ack();
                             pkt->setId(1);
                             send(pkt,out);
            }
            else
            {
                mypkt* pkt=new mypkt();
                       pkt->setId(0);
                       send(pkt,out);
            }
        }
    }

}
