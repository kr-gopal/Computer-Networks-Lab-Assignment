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
       In1 = gate("in1");
       In2 = gate("in2");
       Out1 = gate("out1");
       Out2 = gate("out2");
    // TODO - Generated method body
}

void Hub::handleMessage(cMessage *msg)
{
    if(msg->getArrivalGate()==In1)
        send(msg,Out2);
    else
        send(msg,Out1);
    // TODO - Generated method body
}
