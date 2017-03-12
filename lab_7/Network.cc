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

#include "Network.h"
#include "A_PDU_m.h"
#include "N_PDU_m.h"
#include "R_PDU_m.h"
Define_Module(Network);

void Network::initialize()
{
    // TODO - Generated method body
    Fal=gate("Fal");
    Tal=gate("Tal");
    Tdl1=gate("Tdl1");
    Tdl2=gate("Tdl2");
    Tdl3=gate("Tdl3");
    Tdl4=gate("Tdl4");
    Tdl5=gate("Tdl5");
    Fdl1=gate("Fdl1");
    Fdl2=gate("Fdl2");
    Fdl3=gate("Fdl3");
    Fdl4=gate("Fdl4");
    Fdl5=gate("Fdl5");
    id=par("id");
    delay =4.0;
    if(id==1)
    {
        forwardingTable[1]=make_pair(0,make_pair(-1,Tdl1));//Self
        forwardingTable[2]=make_pair(5,make_pair(-1,Tdl2));
        forwardingTable[3]=make_pair(2,make_pair(-1,Tdl3));
        forwardingTable[4]=make_pair(3,make_pair(-1,Tdl4));
        forwardingTable[5]=make_pair(INT_MAX,make_pair(3,Tdl3));
        cMessage * msg=new cMessage("Self Message");
        scheduleAt(0,msg);
    }
    else if(id==2)
    {
        forwardingTable[1]=make_pair(5,make_pair(-1,Tdl1));
        forwardingTable[2]=make_pair(0,make_pair(-1,Tdl2));//Self
        forwardingTable[3]=make_pair(4,make_pair(-1,Tdl3));
        forwardingTable[4]=make_pair(INT_MAX,make_pair(1,Tdl1));
        forwardingTable[5]=make_pair(3,make_pair(-1,Tdl5));
    }
    else if(id==3)
    {
        forwardingTable[1]=make_pair(2,make_pair(-1,Tdl1));
        forwardingTable[2]=make_pair(4,make_pair(-1,Tdl2));
        forwardingTable[3]=make_pair(0,make_pair(-1,Tdl3));//Self
        forwardingTable[4]=make_pair(INT_MAX,make_pair(1,Tdl1));
        forwardingTable[5]=make_pair(4,make_pair(-1,Tdl5));
    }
    else if(id==4)
    {
        forwardingTable[1]=make_pair(3,make_pair(-1,Tdl1));
        forwardingTable[2]=make_pair(INT_MAX,make_pair(1,Tdl1));
        forwardingTable[3]=make_pair(INT_MAX,make_pair(1,Tdl1));
        forwardingTable[4]=make_pair(0,make_pair(-1,Tdl4));//Self
        forwardingTable[5]=make_pair(INT_MAX,make_pair(1,Tdl1));
    }
    else if(id==5)
    {
        forwardingTable[1]=make_pair(INT_MAX,make_pair(3,Tdl3));
        forwardingTable[2]=make_pair(3,make_pair(-1,Tdl2));
        forwardingTable[3]=make_pair(4,make_pair(-1,Tdl3));
        forwardingTable[4]=make_pair(INT_MAX,make_pair(3,Tdl3));
        forwardingTable[5]=make_pair(0,make_pair(-1,Tdl5));//Self
    }
}

void Network::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        map<int,pair<int,pair<int,cGate*>>> ::iterator itr;
        R_PDU *rpdu=new R_PDU();
        rpdu->setM(forwardingTable);
        for(itr=forwardingTable.begin();itr!=forwardingTable.end();itr++)
        {
            if(itr->second.first!=INT_MAX && itr->second.first!=0 &&itr->second.second.first==-1)
            {
                rpdu->setCost(itr->second.first);
                send(rpdu->dup(),itr->second.second.second);
            }
        }
    }
    else if(strcmp(msg->getClassName(),"R_PDU")==0)
    {
        R_PDU *rpdu=check_and_cast<R_PDU *>(msg);
        map<int,pair<int,pair<int,cGate*>>> tempTable;
        tempTable=rpdu->getM();
        int cost=rpdu->getCost();
        EV<<cost<<"\n";
        map<int,pair<int,pair<int,cGate*>>>:: iterator itr,itr1;
        for(itr=tempTable.begin();itr!=tempTable.end();itr++)
        {
//            EV<<itr->first<<" ";
//            EV<<itr->second.first+cost<<" cd";
            pair<int,cGate*> p;
            p=itr->second.second;
            if(itr->second.first!=INT_MAX )
            tempTable[itr->first]=make_pair(itr->second.first+cost,p);
        }
        EV<<"DONE TILL\n";
        bool change=false;
        for(itr=tempTable.begin(),itr1=forwardingTable.begin();itr!=tempTable.end();itr++,itr1++)
        {
            if(itr->second.first<itr1->second.first)
            {
                change=true;
                forwardingTable[itr1->first]=make_pair(itr->second.first,make_pair(itr->second.second.first,itr1->second.second.second));
            }
        }
        if(change)
        {
            R_PDU *rpdu1=new R_PDU();
            rpdu1->setM(forwardingTable);
            for(itr=forwardingTable.begin();itr!=forwardingTable.end();itr++)
            {
                if(itr->second.first!=INT_MAX && itr->second.first!=0 && itr->second.second.first==-1)
                {
                    rpdu1->setCost(itr->second.first);
                    send(rpdu1->dup(),itr->second.second.second);
                }
            }
        }
    }
    else if(msg->getArrivalGate()==Fal)
    {
      //  EV<<"YAHA BHI AAYA YAR!";
        N_PDU *npdu=new N_PDU();
        A_PDU *apdu=check_and_cast<A_PDU*>(msg);
        npdu->encapsulate(apdu);
        npdu->setSrc(apdu->getSrc());
        npdu->setDest(apdu->getDest());
        int key=apdu->getDest();
        cGate* where=forwardingTable[key].second.second;
        npdu->setType(apdu->getType());
        send(npdu,where);
    }
    else
    {
            N_PDU *npdu=check_and_cast<N_PDU*>(msg);
            if(npdu->getDest()==id)
            {
                send(npdu->decapsulate(),Tal);
            }
            else
            {
                cGate * where=forwardingTable[npdu->getDest()].second.second;
                send(npdu,where);
            }
    }
}
void Network:: finish()
{
    map<int,pair<int,pair<int,cGate*>>>:: iterator itr;
    EV<<"Node is "<<"N"<<id<<"\n";
    for(itr=forwardingTable.begin();itr!=forwardingTable.end();itr++)
    {
        pair<int,pair<int,cGate*>> p;
        p=itr->second;
        EV<<"Destination is "<<itr->first<<"Cost "<<p.first<<"\n";//<<" Cost is "<<itr->second.first<<endl;
    }
}
