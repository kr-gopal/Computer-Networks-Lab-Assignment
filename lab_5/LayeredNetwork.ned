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

//
// TODO auto-generated type
//
network LayeredNetwork
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
    submodules:
        n1: Node {
            NodeId = 1;
            @display("p=38,132");
        }
        h1: Hub {
            hubId = 1;
            @display("p=82,31");
        }
        n2: Node {
            NodeId = 2;
            @display("p=143,132");
        }
    connections:
        n1.gOut --> Channel --> h1.gIn1;
        n2.gIn <-- Channel <-- h1.gOut1;
        n2.gOut --> Channel --> h1.gIn2;
        n1.gIn <-- Channel <-- h1.gOut2;
}
