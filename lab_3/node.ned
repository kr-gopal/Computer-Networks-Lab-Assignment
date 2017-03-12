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

package lab2;

module Node
{
    parameters:
        int id;
    gates:
        input gin;
        output gout;

    submodules:
        AL: Application
        {
            node_id = id;
            msg_count=0;
        }
        DL: Datalink
         {
            node_id = id;
            count=0;
        }
        PL: Physical
        {
            node_id = id;
        }
        
    connections:
        AL.gout --> DL.gin1;
        AL.gin <-- DL.gout1;
        DL.gin2 <-- PL.gout1;
        DL.gout2 --> PL.gin1;
        PL.gout2 --> gout;
        PL.gin2 <-- gin; 
	}
	
   network LayerNetwork
   {
       submodules:
        n1: Node {id=1;}
        n2: Node{id=2;}
        hub: Hub;
  	  connections:
        n1.gout-->{delay = 100ms;}-->hub.in1;
         hub.out2-->{delay = 100ms;}-->n2.gin;
        n2.gout-->{delay = 100ms;}-->hub.in2;
        hub.out1-->{delay = 100ms;}-->n1.gin;
	}
