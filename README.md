# Castelli2275
CSCI 2275 Final Project

Project Summary
This project will use a graph data structure to create basic simulation of a mobile wireless network. The purpose of the graph is to model simple network parameters in order to elect the best path to transmit data through the network. Vertices will be individual radios. Edges will connect radios that receive a signal greater than the radios minimum sensetivity. Recieved signal stength will be compared to an array of throughput and sensetivity to determine theoretical throughput capacity. Because maximum throughput is desirable, the edge weigts will use the inverse of the throughput value so that Dijkstra's can be used to determine the best paths for data to pass through the network. 

Currently out of scope:
The weighting may be non-linear as a hop through one radio to get to another beyond it will incur a penalty, as opposed to a direct connection. It was determined that the use of inverted throughput values is sufficient in selecting reasonable paths. A more advanced version of Dijkstra's may prove to be a more advanced route selection algorithm (file:///C:/Users/jcastelli/Downloads/algorithms-13-00269-v2.pdf), but is out of scope at this time.

The current output will be  observed when the code is run:
Edges and weights for all radios at each input timestep
At the end of the simulation: 
the final cost of each radio to comunicate with any other radio in the network (for the final radio positions)
the best path of each radio to route data to each other radio in the network (for the final radio positions)

The included input file forms a simple 5 radio network. R1 is a static radio. R2 and R3 have a linear motion. R4 and R5 have a circular orbit motion.


Run Instructions
This is simulation that is not time constrained and requires  few user input:
1) Node list input file - initializes radio nodes
2) the user to input a simulation time. This is the amount of time to be simulated. The simulation runs significantly faster than real time.
3) time step (dt) that the simulation will run at.
The run line below runs a 90 second simulation with a timestep (dt) of 3 seconds.

compile from command line using VScode:
g++ -std=c++11 Project_Castelli.cpp Radio.cpp Graph_Castelli.cpp -o FinalProject

run from command line:
.\FinalProject NodeList.txt 90 3


Dependencies
None

System Requirements
Currently tested with VS code 1.51.1

Team Members
Jon Castelli

Contributors

Open Issues/Bugs
Could use a better way to display/process outputs
input file handling
