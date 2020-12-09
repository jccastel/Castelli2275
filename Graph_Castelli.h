#ifndef GRAPH_CASTELLI_H
#define GRAPH_CASTELLI_H
#include<vector>
#include<iostream>
#include "Radio.h"

using namespace std;

struct vertex;

struct adjVertex{
    vertex *v;
    double weight;
    adjVertex(vertex* verty, double weightIn) {
        v = verty;
        weight = weightIn;
    }
};

struct vertex{
    string name;
    Radio r;
    vertex *parent = nullptr;
    bool visited;
    double distance = (double) INT_MAX;
    double cost = (double) INT_MAX;
    vector<adjVertex*> adj;
    vertex() {        
        visited = false;
    }
};

class Graph
{
    public:
        Graph();  
        ~Graph(); 
        void computeEdges();
        void addVertex(string n);
        void displayEdges();   
        void updateNodes(double dt);
        void dijkstra();
        void pathBack();
    protected:
    private:
        vector<vertex*> vertices;
        vertex* getMinNode();
        vertex* getMaxNode();
        bool allVisitedCheck();
};

#endif // GRAPH_CASTELLI_H
