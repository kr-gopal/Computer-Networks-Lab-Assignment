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

#include "phy_layer_GBN.h"
#include "DLL_PKT_m.h"
#include "PL_PKT_m.h"

Define_Module(Phy_layer_GBN);

void Phy_layer_GBN::initialize()
{
    // TODO - Generated method body
    PhyLId = par("PhyLId");
    gDLLIn = gate("gDLIn");
    gNodeIn = gate("gNodeIn");
    gNodeOut = gate("gNodeOut");
    gDLLOut = gate("gDLOut");
    lostPkt = 3;
}

void Phy_layer_GBN::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(uniform(0,1) < 0.5 && lostPkt > 0){
        EV << "Packet Lost " <<endl;
        lostPkt--;
        delete msg;
    }
    else if(msg->getArrivalGate() == gDLLIn){
        DLL_PKT* dlPkt = check_and_cast<DLL_PKT*>(msg);
        PL_PKT* phyPkt = new PL_PKT();
        phyPkt->setId(dlPkt->getId());
        phyPkt->setName(dlPkt->getName());
        phyPkt->setType(dlPkt->getType());
        phyPkt->encapsulate(dlPkt);
        send(phyPkt,gNodeOut);
    }
    else if(msg->getArrivalGate() == gNodeIn){
        PL_PKT* phyPkt = check_and_cast<PL_PKT*>(msg);
        send(phyPkt,gDLLOut);
    }
    else
        delete msg;
}
