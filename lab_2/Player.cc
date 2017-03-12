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

#include "Player.h"
#include "dlpdu_m.h"
#include "alpdu_m.h"
#include "plpdu_m.h"

Define_Module(Player);

void Player::initialize()
{
    id=par("id");
}

void Player::handleMessage(cMessage *msg)
{
    P_PDU* p=new P_PDU();
    if(msg -> getArrivalGate()== gate("ginup"))
    {
        DL_PDU* pkt = check_and_cast<DL_PDU*> (msg);
        p->encapsulate(pkt);
        send(p,gate("goutdown"));
    }
    else if(msg -> getArrivalGate()== gate("gindown"))
    {
        P_PDU* pkt = check_and_cast<P_PDU*> (msg);
        send(pkt->decapsulate(),gate("goutup"));
    }
}
