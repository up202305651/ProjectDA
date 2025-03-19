#include "graph.h"
#include "MutablePriorityQueue.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

void Graph::dijkstraShortestPath(int src, int dest) {
    dist.clear(); // Reset previous distances
    unordered_map<int, Vertex*> prev;
    MutablePriorityQueue<Vertex> pq;

    // Initialize distances
    for (Vertex *v : vertexSet) {
        dist[v->getId()] = numeric_limits<double>::infinity();
        prev[v->getId()] = nullptr;
    }

    // Find source and destination vertices
    Vertex *start = findVertex(src);
    Vertex *end = findVertex(dest);
    if (!start || !end) {
        cout << "Error: Invalid source or destination." << endl;
        return;
    }

    // Set source distance to 0 and add to priority queue
    dist[src] = 0;
    pq.insert(start);

    while (!pq.empty()) {
        Vertex *u = pq.extractMin();
        int uID = u->getId();

        if (u == end) break;

        for (Edge *e : u->getAdj()) {
            Vertex *v = e->getDest();
            int vID = v->getId();
            double alt = dist[uID] + e->getWeightDriving(); // Use driving weight

            if (alt < dist[vID]) {
                dist[vID] = alt;
                prev[vID] = u;
                pq.decreaseKey(v);
            }
        }
    }

    // Build and print the path
    vector<int> path;
    for (int at = dest; at != 0; at = prev[at] ? prev[at]->getId() : 0) {
        path.insert(path.begin(), at);
    }

    if (path.empty() || path.front() != src) {
        cout << "No path found from " << src << " to " << dest << endl;
        return;
    }

    double totalDriving = dist[dest];
    double totalWalking = 0;

    cout << "Shortest Path (Driving) from " << src << " to " << dest << ":\n";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";

        if (i < path.size() - 1) {
            Vertex *current = findVertex(path[i]);
            Vertex *next = findVertex(path[i + 1]);
            for (Edge *e : current->getAdj()) {
                if (e->getDest() == next) {
                    totalWalking += e->getWeightWalking();
                    break;
                }
            }
        }
    }
    cout << "\nTotal Driving Distance: " << totalDriving << "\n";
    cout << "Total Walking Distance: " << totalWalking << "\n";
}

