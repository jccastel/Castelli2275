#include "Graph_Castelli.h"
#include "Radio.h"
#include <vector>
#include <iostream>
#include <queue>
#include <stack> 
#include <fstream>
#include <sstream>
using namespace std;

Graph::Graph(){}

Graph::~Graph(){
    //dtor
}

void Graph::computeEdges(){

    for (int i = 0; i < vertices.size(); i++) {
        //pop all adj vertices to clear and then update
        int num_edges = vertices[i]->adj.size();
        for (int j = 0; j < num_edges; j++)
            vertices[i]->adj.pop_back();
    }

    for (int i = 0; i < vertices.size(); i++) {
        //update edges
        for (int j = 0; j < vertices.size(); j++) {
            //Dijkstra's is based off of a shortest path, minimum cost principle. In a network,
            //our edges are weighted with theoretical throughput. the higher the throughput, the better.
            //Therefor we assign the inverse of the theoretical throughput as the weight.
            double weight = 0;
            if (i == j) 
                weight = 1/100; //will always be shortest path to itself
            else {
                double txRate = vertices[i]->r.getTXrate(vertices[j]->r.getNode());
                if (txRate == 0)
                    weight = 10;// avoids divide by zero, weights>10 are not recognized as having sufficient throughput to be effective
                else
                    weight = 1/txRate;
            }
            if (weight < 10) {//weights > 10 should not be included in the network
                adjVertex* av = new adjVertex(vertices[j],weight);
                vertices[i]->adj.push_back(av);
            }
        }
    }
}

void Graph::addVertex(string line){
    string n;
    stringstream lineStream(line);
    getline(lineStream, n, ',');
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == n){
            found = true;
            cout<<vertices[i]->name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex* v = new vertex();
        radioNode r;
        v->name = n;
        getline(lineStream, n, ',');
        r.power = stod(n);
        getline(lineStream, n, ',');
        r.gain = stod(n);
        getline(lineStream, n, ',');
        r.xo = stod(n);
        r.x = r.xo;
        getline(lineStream, n, ',');
        r.yo = stod(n);
        r.y = r.yo;
        getline(lineStream, n, ',');
        r.h = stod(n);
        getline(lineStream, n, ',');
        r.r = stod(n);
        getline(lineStream, n, ',');
        r.v = stod(n);
        getline(lineStream, n, ',');
        r.motion_model = stoi(n);
        if (r.motion_model > 2)
            r.motion_model = 0;//default to static
        if (r.motion_model == 2)
            r.y = r.yo + r.r;        

        v->r.setNode(r);
        vertices.push_back(v);
    }
}

void Graph::displayEdges()
{
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<"->";
        for(int j = 0; j < vertices[i]->adj.size(); j++){
            cout.precision(3);
            cout<<vertices[i]->adj[j]->v->name<<"("<< vertices[i]->adj[j]->weight <<")";
            if (j != vertices[i]->adj.size()-1)
                cout<<"->";
        }
        cout << endl;
    }
    cout << endl;
}

void Graph::updateNodes(double dt) {
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i]->r.updatePosition(vertices[i]->name, dt);         
    }
}

//getMinNode() will return the node with the lowest cost that has not yet been visited
vertex* Graph::getMinNode() {
    int min = INT32_MAX;
    vertex* result = vertices[0];
    for (int i = 0; i < vertices.size(); i++) {
        if (!vertices[i]->visited) {
            if (vertices[i]->cost < min) {
                min = vertices[i]->cost;
                result = vertices[i];
            }
        }
    }
    return result;
}

//allVisitedCheck() will return true if all nodes have been visited 
bool Graph::allVisitedCheck() {
    for (int i = 0; i < vertices.size(); i++) {
        if (!vertices[i]->visited) {
            return false;
        }
    }
    return true;
}

//go through each node and update its cost from the src.
//thus creating a minimum spanning tree where each node has its min cost from the source.
//after making these values print them all
void Graph::dijkstra() {
    for (int j = 0; j < vertices.size(); j++)
    {
        vertex* source = vertices[j];
        source->cost = 0;

        while (!allVisitedCheck()) {
            vertex* minNode = getMinNode();
            minNode->visited = true;

            for (int i = 0; i < minNode->adj.size(); i++) {
                if (minNode->adj[i]->v->cost > minNode->cost + minNode->adj[i]->weight) {

                    minNode->adj[i]->v->cost = minNode->cost + minNode->adj[i]->weight;
                    minNode->adj[i]->v->parent = minNode;
                }
            }
        }

        cout << "Radio: " << vertices[j]->name << endl;
        for (int i = 0; i < vertices.size(); i++)
        {
            cout.precision(3);
            cout << vertices[i]->name << " reached with cost:" << vertices[i]->cost << endl;
        }
        pathBack();
        cout << endl;
        for (int i = 0; i < vertices.size(); i++) {
            vertices[i]->visited = false;
            vertices[i]->cost = INT32_MAX;
            vertices[i]->parent = nullptr;
        }
    }
}

void Graph::pathBack() {    
    for (vertex* e : vertices) {
        vertex* temp = e;
        while (temp != nullptr) {
            cout << temp->name;
            if (temp->parent != nullptr) {
                cout << "->";
            }
            temp = temp->parent;
        }
        cout << endl;
    }
}