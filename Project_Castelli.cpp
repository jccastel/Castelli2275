#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include "Graph_Castelli.h"

using namespace std; 

void die(string message) {
    cout << message << endl;
    exit(0);
}

void generate_graph(Graph* g, std::string filename) {
    ifstream file(filename);

    // non-existant or corrupted file
    if (file.fail()) {
        die("Check if file exists!");
    }

    // read in vertices
    string line;
    getline(file, line);
    while (getline(file, line)) 
        g->addVertex(line);

    // compute inital edges
    g->computeEdges();
}

//int main(int argc, const char * argv[]) {// cmdl
int main(){
    Graph g;
    string filename("nodeList.txt");//vs19
    generate_graph(&g, filename);
    g.displayEdges();

    double dt = 3;
    double t = 0;
    int t_end = 90;

    while (t<t_end) {
        g.updateNodes(dt);
        g.computeEdges();//update edges based of of new radio positions
        g.displayEdges();
        
        t = t + dt;
    }

    g.dijkstra();
    return 0;
}
