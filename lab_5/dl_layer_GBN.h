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

#ifndef __LAB5_DL_LAYER_GBN_H_
#define __LAB5_DL_LAYER_GBN_H_

#include <omnetpp.h>
#include <vector>
#include <AL_PKT_m.h>
#include <DLL_PKT_m.h>
#include <PL_PKT_m.h>
#include "pktHandle_m.h"

using namespace std;

/**
 * TODO - Generated class
 */
class Dl_layer_GBN : public cSimpleModule
{
  private:
    int DLLId;
    cGate* gAppIn;
    cGate* gAppOut;
    cGate* gPhyIn;
    cGate* gPhyOut;
    simtime_t timeout;
    PktHandle *sendPkt;
    cMessage *handle;
    vector<cMessage*> pktVector;
    vector<cMessage*> timeOutEvent;
    simtime_t D_p;
    simtime_t D_pr;
    int window;
    int sentFrame;
    int crrPkt;
    int sf,sl,sn;
    int rn;
    int pktSent;
    int maxReceived;
    cLongHistogram roundDelayCountStats;
    cOutVector roundDelayCountVector;
    cMessage *message;
    int numSent;
    int numReceived;
    simtime_t initialTime;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual DLL_PKT* getNewDataPkt(AL_PKT *appPkt);
    virtual DLL_PKT* getDataAckPkt(int id);
    virtual int min(int a,int b);
    virtual void finish();
};

#endif
