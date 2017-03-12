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

package lab6;

module Node
{
    parameters:
        int node_id;
    gates:
        input gin[];
        output gout[];
        
    submodules:
        AL: Al
        {
            id=node_id;
           
        }
        NL: Nl
        {
            id=node_id;
        }
        
        DL: Dl
         {
            id=node_id;
           
            
        }
        PL: Pl
        {
            id=node_id;
           
        }
        
    connections:
        AL.gAout --> NL.gNin1;
        AL.gAin <-- NL.gNout1;
        NL.gNout2--> DL.gDin1++;
        NL.gNin2 <-- DL.gDout1++;
        DL.gDin2++ <-- PL.gPout1++;
        DL.gDout2++ --> PL.gPin1++;
        PL.gPout2++ --> gout++;
        PL.gPin2++ <-- gin++;
        
}
        network forwardingNetwork
		{	
   		 submodules:
        n1: Node{node_id=1;}
        n2: Node{node_id=2;}
        n3: Node{node_id=3;}
        n4: Node{node_id=4;}
        n5: Node{node_id=5;}
        hub1: Hub;
        hub2: Hub;
        hub3: Hub;
        hub4: Hub;
        hub5: Hub;
        hub6: Hub;
  	  connections:
        n1.gout++-->{delay = 100ms;}-->hub1.in1;
         hub1.out2-->{delay = 100ms;}-->n2.gin++;
        n2.gout++-->{delay = 100ms;}-->hub1.in2;
        hub1.out1-->{delay = 100ms;}-->n1.gin++;
        
        n2.gout++-->{delay = 100ms;}-->hub2.in1;
         hub2.out2-->{delay = 100ms;}-->n3.gin++;
        n3.gout++-->{delay = 100ms;}-->hub2.in2;
        hub2.out1-->{delay = 100ms;}-->n2.gin++;
        
        n2.gout++-->{delay = 100ms;}-->hub3.in1;
         hub3.out2-->{delay = 100ms;}-->n5.gin++;
        n5.gout++-->{delay = 100ms;}-->hub3.in2;
        hub3.out1-->{delay = 100ms;}-->n2.gin++;
        
        n3.gout++-->{delay = 100ms;}-->hub4.in1;
         hub4.out2-->{delay = 100ms;}-->n5.gin++;
        n5.gout++-->{delay = 100ms;}-->hub4.in2;
        hub4.out1-->{delay = 100ms;}-->n3.gin++;
        
        n1.gout++-->{delay = 100ms;}-->hub5.in1;
         hub5.out2-->{delay = 100ms;}-->n3.gin++;
        n3.gout++-->{delay = 100ms;}-->hub5.in2;
        hub5.out1-->{delay = 100ms;}-->n1.gin++;
        
        n1.gout++-->{delay = 100ms;}-->hub6.in1;
         hub6.out2-->{delay = 100ms;}-->n4.gin++;
        n4.gout++-->{delay = 100ms;}-->hub6.in2;
        hub6.out1-->{delay = 100ms;}-->n1.gin++;
        
		
		}
         
	

