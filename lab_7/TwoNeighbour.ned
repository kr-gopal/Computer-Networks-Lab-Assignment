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

module TwoNeighbour
{
     parameters:
        int nodeid;
        int noOfPackets;
        int source;
        int destin;
    gates:
        input Fn3;
        input Fn2;
        output Tn3;
        output Tn2;
       
       submodules:
        al: ALayer {
            id = nodeid;
            numPackets=noOfPackets;
            src=source;
            dest=destin;
            @display("p=320,241");
        }
        dll2: DlLayer {
            id = nodeid;
            @display("p=144,156");
        }
        dll3: DlLayer {
            id = nodeid;
            @display("p=131,267");
        }
        nw: Network {
            id = nodeid;
            @display("p=256,217");
        }
        pl2: PLayer {
            id = nodeid;
            @display("p=61,156");
        }
        pl3: PLayer {
            id = nodeid;
            @display("p=61,280");
        }
        connections:
        al.Tnw --> nw.Fal;
        nw.Tdl2 --> dll2.Fnw;
        nw.Tdl3 --> dll3.Fnw;
        
        dll2.Tpl --> pl2.Fdl;
        dll3.Tpl --> pl3.Fdl;
        
        pl2.Fnode <-- Fn2;
        pl2.Tnode --> Tn2;
        pl3.Fnode <-- Fn3;
        pl3.Tnode --> Tn3;
        pl2.Tdl --> dll2.Fpl;
        pl3.Tdl --> dll3.Fpl;
        
        dll2.Tnw --> nw.Fdl2;
        dll3.Tnw --> nw.Fdl3;
        nw.Tal --> al.Fnw;
}
