#include "graph.h"
#include "MutablePriorityQueue.h"
#include <iostream>
#include <limits.h>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;
/*
void Graph::dijkstraWalking(int src, int dest) {
    unordered_map<int, double> dist;
    unordered_map<int, Vertex*> prev;
    priority_queue<pair<double, Vertex*>, vector<pair<double, Vertex*>>, greater<>> pq;

    // Initialize distances
    for (Vertex* v : vertexSet) {
        dist[v->getId()] = INT_MAX;
    }

    Vertex* start = findVertex(src);
    if (!start) {
        cout << "Source vertex not found!" << endl;
        return;
    }

    dist[src] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        if (currentDist > dist[u->getId()]) continue;

        for (Edge* edge : u->getAdj()) {
            Vertex* v = edge->getDest();
            double weight = edge->getWeightWalking();

            if (dist[u->getId()] + weight < dist[v->getId()]) {
                dist[v->getId()] = dist[u->getId()] + weight;
                prev[v->getId()] = u;
                pq.push({dist[v->getId()], v});
            }
        }
    }

    // Print result
    if (dist[dest] == INT_MAX) {
        cout << "No path found from " << src << " to " << dest << " by walking." << endl;
    } else {
        cout << "Shortest walking distance from " << src << " to " << dest << " is: " << dist[dest] << " meters." << endl;
    }
}
*/

bool relax(Edge *edge) { // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDist() + edge->getWeightDriving() < edge->getDest()->getDist()) {
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWeightDriving());
        edge->getDest()->setPath(edge);
        return true;
    }
    return false;
}

void dijkstraDriving(Graph *g, const int &origin, const int &destination) {
    Vertex *origem = g->findVertex(origin);
    if (!origem) {
        cout << "Source vertex not found!" << endl;
        return;
    }

    int maxi = INT_MAX;
    for (Vertex *v : g->getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
        v->setDist(maxi);
    }
    origem->setDist(0);

    MutablePriorityQueue<Vertex> queue;
    for (Vertex *v : g->getVertexSet()) {
        queue.insert(v);
    }

    while (!queue.empty()) {
        Vertex *min = queue.extractMin();

        for (Edge *edge : min->getAdj()) {
            Vertex *destino = edge->getDest();
            if (relax(edge)) {
                queue.decreaseKey(destino);
            }
        }
    }

    if (g->findVertex(destination)->getDist() == INT_MAX) {
        cout << "No path found from " << origin << " to " << destination << " by driving." << endl;
    } else {
        cout << "Shortest driving time from " << origin << " to " << destination << " is: "
             << g->findVertex(destination)->getDist() << " minutes." << endl;
    }
}