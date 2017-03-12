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

package lab7;

module OneNeighbour
{
     parameters:
        int nodeid;
        int noOfPackets;
        int source;
        int destin;
    gates:
        input Fn1 ;
        output Tn1;
    submodules:
        al: ALayer {
            id = nodeid;
            numPackets=noOfPackets;
            src=source;
            dest=destin;
            @display("p=320,241");
        }
        dll1: DlLayer {
            id = nodeid;
            @display("p=183,108");
        }
        
        nw: Network {
            id = nodeid;
            @display("p=256,217");
        }
        pl1: PLayer {
            id = nodeid;
            @display("p=61,95");
        }
        
    connections:
        al.Tnw --> nw.Fal;
        nw.Tdl1 --> dll1.Fnw;
        dll1.Tpl --> pl1.Fdl;
        pl1.Tdl --> dll1.Fpl;
        pl1.Fnode <-- Fn1;
        pl1.Tnode --> Tn1;
        dll1.Tnw --> nw.Fdl1;
        nw.Tal --> al.Fnw;
}
