#include "graph.h"
#include "MutablePriorityQueue.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <set>

using namespace std;

void generateRestrictedGraph(Graph& g, const set<int>& avoidNodes, const set<pair<int, int>>& avoidSegments, int includeNode) {
    // remove nodes to avoid
    for (int nodeId : avoidNodes) {
        g.removeVertex(nodeId);
    }

    // remove edges to avoid
    for (const auto& segment : avoidSegments) {
        g.removeEdge(segment.first, segment.second);
    }

    // if includeNode is specified, ensure it is in the graph
    if (includeNode != -1 && !g.findVertex(includeNode)) {
      g.addVertex(includeNode, "includeNode", 0);
    }
}

void dijkstraRestricted(Graph g, int src, int dest, const set<int>& avoidNodes, const set<pair<int, int>>& avoidSegments, int includeNode) {
    generateRestrictedGraph(g, avoidNodes, avoidSegments, includeNode);

    unordered_map<int, double> dist;
    unordered_map<int, Vertex*> prev;
    priority_queue<pair<double, Vertex*>, vector<pair<double, Vertex*>>, greater<>> pq;

    // Initialize distances
    for (Vertex* v : g.getVertexSet()) {
        dist[v->getId()] = numeric_limits<double>::infinity();
    }

    Vertex* start = g.findVertex(src);
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
            double weight = edge->getWeightDriving();

            if (dist[u->getId()] + weight < dist[v->getId()]) {
                dist[v->getId()] = dist[u->getId()] + weight;
                prev[v->getId()] = u;
                pq.push({dist[v->getId()], v});
            }
        }
    }

    // Print result
    if (dist[dest] == numeric_limits<double>::infinity()) {
        cout << "No path found from " << src << " to " << dest << " by Car." << endl;
    } else {
        cout << "Shortest driving distance from " << src << " to " << dest << " is: " << dist[dest] << " meters." << endl;
    }
}