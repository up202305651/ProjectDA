#include "graph.h"
#include "MutablePriorityQueue.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

void Graph::dijkstraWalking(int src, int dest) {
    unordered_map<int, double> dist;
    unordered_map<int, Vertex*> prev;
    priority_queue<pair<double, Vertex*>, vector<pair<double, Vertex*>>, greater<>> pq;

    // Initialize distances
    for (Vertex* v : vertexSet) {
        dist[v->getId()] = numeric_limits<double>::infinity();
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
    if (dist[dest] == numeric_limits<double>::infinity()) {
        cout << "No path found from " << src << " to " << dest << " by walking." << endl;
    } else {
        cout << "Shortest walking distance from " << src << " to " << dest << " is: " << dist[dest] << " meters." << endl;
    }
}