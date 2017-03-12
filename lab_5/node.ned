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

package lab5;

module Node
{
    parameters:
        int NodeId;
    gates:
        input gIn;
        output gOut;
    submodules:
        AppL:App_layer_GBN{AppLId=NodeId;}
        DLL:Dl_layer_GBN{DLLId=NodeId;}
        PhyL:Phy_layer_GBN{PhyLId=NodeId;}
    connections:
        AppL.gDLIn<--DLL.gAppOut;
        AppL.gDLOut-->DLL.gAppIn;
        DLL.gPhyIn<--PhyL.gDLOut;
        DLL.gPhyOut-->PhyL.gDLIn;
        PhyL.gNodeIn<--gIn;
        PhyL.gNodeOut-->gOut;
}
