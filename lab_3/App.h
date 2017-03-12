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

#ifndef __LAB2_APPLICATION_H_
#define __LAB2_APPLICATION_H_

#include <omnetpp.h>

/**
 * TODO - Generated class
 */
class Application : public cSimpleModule
{
private:
        simtime_t timeout;  // timeout
        cMessage *timeoutEvent;  // holds pointer to the timeout self-message
    protected:
    cGate* gIn;
       cGate* gOut;
       int node_id;
       int msg_count;

       //int count;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
