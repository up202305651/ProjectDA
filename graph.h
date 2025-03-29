#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;
#include <unordered_map>
#include <queue>
#include "MutablePriorityQueue.h"

using namespace std;

class Edge;
class Vertex;

class Vertex {
public:
    Vertex(int id, string code, int parking);
    bool operator<(Vertex &vertex) const;

    int getId() const;
    string getCode() const;
    int hasParking() const;
    vector<Edge *> getAdj() const;
    bool getAvoidVertex() const;
    void setAvoidVertex(bool value);
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    vector<Edge *> getIncoming() const;

    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setIndegree(unsigned int indegree);
    void setReverse(Edge *reverse);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge *addEdge(Vertex *dest, double driving, double walking);
    bool removeEdge(int id);
    void removeOutgoingEdges();

    int queueIndex = 0; // Required for MutablePriorityQueue
    friend class MutablePriorityQueue<Vertex>;
protected:
    int id;
    string code;
    bool avoid=false;
    int parking;
    vector<Edge *> adj;
    vector<Edge *> incoming;

    bool visited = false;
    bool processing = false;
    unsigned int indegree = 0;
    double dist = 0;
    Edge *path = nullptr;

};


class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double driving, double walking);

    Vertex *getDest() const;
    double getWeightWalking() const;
    double getWeightDriving() const;
    Vertex *getOrig() const;
    Edge *getReverse() const;
    bool getAvoidEdge() const;
    void setAvoidEdge(bool value);
    

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);

protected:
    Vertex *orig;
    Vertex *dest;
    double driving;
    double walking;
    Edge *reverse = nullptr;
    bool avoid=false;
};

class Graph {
public:
    ~Graph();
    Vertex *findVertex(int id) const;
    bool addVertex(int id,string code, int parking);
    bool removeVertex(int id);
    bool addEdge(int src, int dest, double driving, double walking);
    bool addBidirectionalEdge(int source, int dest, double driving, double wwalking);
    bool removeEdge(int src, int dest);
    int getNumVertex() const;
    int findVertexIdx(int id) const;
    vector<Vertex *> getVertexSet() const;

    void loadLocations(const string& filename);
    void loadDistances(const string& filename);
    void printGraph() const;

protected:
    unordered_map<int, double> dist;
    vector<Vertex *> vertexSet;// Maps location codes to their numeric IDs
};



#endif