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

#include "Nl.h"

Define_Module(Nl);

void Nl::initialize()
{
        gNIn1 = gate("gNin1");
        gNIn2 = gate("gNin2");
        gNOut1 = gate("gNout1");
        gNOut2 = gate("gNout2");
        node_id = par("id");
                n1Ft.insert(pair <int, int, int> (1, -1, 0));
                n1Ft.insert(pair <int, int, int> (1, -1, 5));
                n1Ft.insert(pair <int, int, int> (1, -1, 2));
                n1Ft.insert(pair <int, int, int> (1, -1, 3));
                n1Ft.insert(pair <int, int, int> (1, 3, 6));

                n2Ft.insert(pair <int, int, int> (2, -1, 5));
                n2Ft.insert(pair <int, int, int> (2, -1, 0));
                n2Ft.insert(pair <int, int, int> (2, -1, 4));
                n2Ft.insert(pair <int, int, int> (2, 1, 8));
                n2Ft.insert(pair <int, int, int> (2, -1, 3));

                n3Ft.insert(pair <int, int, int> (3, -1, 2));
                n3Ft.insert(pair <int, int, int> (3, -1, 4));
                n3Ft.insert(pair <int, int, int> (3, -1, 0));
                n3Ft.insert(pair <int, int, int> (3, 1, 5));
                n3Ft.insert(pair <int, int, int> (3, -1, 4));

                n4Ft.insert(pair <int, int, int> (4, -1, 3));
                n4Ft.insert(pair <int, int, int> (4, 1, 8));
                n4Ft.insert(pair <int, int, int> (4, 1, 5));
                n4Ft.insert(pair <int, int, int> (4, -1, 0));
                n4Ft.insert(pair <int, int, int> (4, 1, 9));

                n5Ft.insert(pair <int, int, int> (5, 3, 6));
                n5Ft.insert(pair <int, int, int> (5, -1, 3));
                n5Ft.insert(pair <int, int, int> (5, -1, 4));
                n5Ft.insert(pair <int, int, int> (5, 3, 9));
                n5Ft.insert(pair <int, int, int> (5, -1, 0));
}

void Nl::handleMessage(cMessage *msg)
{

}
