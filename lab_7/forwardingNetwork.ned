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

network ForwardingNetwork
{
    @display("bgb=412,426");
    int packets;
    int src;
    int dest;
    submodules:
        n1: ThreeNeighbourN1 {
            nodeid = 1;
            noOfPackets=packets;
            source=src;
            destin=dest;
            @display("p=50,38");
        }
        n2: ThreeNeighbourN2 {
            nodeid = 2;
            source=src;
            destin=dest;
            noOfPackets=packets;
            @display("p=345,50");
        }
        n3: ThreeNeighbourN3 {
            nodeid = 3;
            noOfPackets=packets;
            source=src;
            destin=dest;
            @display("p=190,163");
        }
        n4: OneNeighbour {
            nodeid = 4;
            noOfPackets=packets;
            source=src;
            destin=dest;
            @display("p=50,305");
        }
        n5: TwoNeighbour {
            nodeid = 5;
            noOfPackets=packets;
            source=src;
            destin=dest;
            @display("p=345,305");
        }
    connections:
	     //n1--n2
		n1.Tn2-->{  delay = 5ms; }-->n2.Fn1;
		n2.Tn1-->{  delay = 5ms; }-->n1.Fn2;		
		//n1--n3
		n1.Tn3-->{  delay = 2ms; }-->n3.Fn1;		
		n3.Tn1-->{  delay = 2ms; }-->n1.Fn3;
		//n1--n4
		n1.Tn4-->{  delay = 3ms; }-->n4.Fn1;
		n4.Tn1-->{  delay = 3ms; }-->n1.Fn4;
		//n5--n3
		n5.Tn3-->{  delay = 4ms; }-->n3.Fn5;
		n3.Tn5-->{  delay = 4ms; }-->n5.Fn3;		
		//n2--n5
		n2.Tn5-->{  delay = 3ms; }-->n5.Fn2;
		n5.Tn2-->{  delay = 3ms; }-->n2.Fn5;		
		//n2--n3
		n2.Tn3-->{  delay = 4ms; }-->n3.Fn2;
		n3.Tn2-->{  delay = 4ms; }-->n2.Fn3;

        
        
}
