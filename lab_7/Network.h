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

#ifndef __LAB6_NETWORK_H_
#define __LAB6_NETWORK_H_
#include <omnetpp.h>
#include<bits/stdc++.h>
using namespace std;
/**
 * TODO - Generated class
 */
class Network : public cSimpleModule
{
    cGate * Fal;
    cGate * Tal;
    cGate * Tdl1;
    cGate *Tdl2;
    cGate *Tdl3;
    cGate *Tdl4;
    cGate *Tdl5;
    cGate * Fdl1;
    cGate* Fdl2;
    cGate* Fdl3;
    cGate* Fdl4;
    cGate* Fdl5;
    simtime_t delay;
    int id;
    map<int,pair<int,pair<int,cGate*>>> forwardingTable;
  protected:
    virtual void finish();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
