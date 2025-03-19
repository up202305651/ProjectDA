#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
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
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    vector<Edge *> getIncoming() const;

    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge *addEdge(Vertex *dest, double driving, double walking);
    bool removeEdge(int id);
    void removeOutgoingEdges();

    int queueIndex = 0; // Required for MutablePriorityQueue

private:
    int id;
    string code;
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

private:
    Vertex *orig;
    Vertex *dest;
    double driving;
    double walking;
};

class Graph {
public:
    ~Graph();
    void dijkstraShortestPath(int src, int dest);
    Vertex *findVertex(int id) const;
    bool addVertex(int id,string code, int parking);
    bool removeVertex(int id);
    bool addEdge(int src, int dest, double driving, double walking);
    bool removeEdge(int src, int dest);
    int getNumVertex() const;
    vector<Vertex *> getVertexSet() const;

    void loadLocations(const string& filename);
    void loadDistances(const string& filename);
    void printGraph() const;
private:
    unordered_map<int, double> dist;
    vector<Vertex *> vertexSet;// Maps location codes to their numeric IDs
    int findVertexIdx(int id) const;
};

#endif
