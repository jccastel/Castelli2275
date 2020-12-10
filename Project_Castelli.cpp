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

int main(int argc, const char * argv[]) {// cmdl
//int main(){
    Graph g;
    string filename(argv[1]);//vs19
    generate_graph(&g, filename);
    g.displayEdges();

    int t_end = stoi(argv[2]);
    double dt = stod(argv[3]);
    if (t_end<dt){        
        t_end ;
        dt = t_end/10;
        cout<<"a3:"<<argv[3]<<" > a2 "<<argv[2]<<",default dt = t_end/10"<<endl;
    }
     
    double t = 0;

    while (t<t_end) {
        g.updateNodes(dt);
        g.computeEdges();//update edges based of of new radio positions
        g.displayEdges();        
        t += dt;
    }

    g.dijkstra();
    return 0;
}
