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

#include "hub.h"

Define_Module(Hub);

void Hub::initialize()
{
    // TODO - Generated method body
    hubId = par("hubId");
    gIn1 = gate("gIn1");
    gIn2 = gate("gIn2");
    gOut1 = gate("gOut1");
    gOut2 = gate("gOut2");
}

void Hub::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->getArrivalGate() == gIn1){
        send(msg,gOut1);
    }
    else if(msg->getArrivalGate() == gIn2){
        send(msg,gOut2);
    }
    else
        delete msg;
}
