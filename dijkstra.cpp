#include <climits>

#include "graph.h"
#include "MutablePriorityQueue.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

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
    Vertex *dest = g->findVertex(destination);
    if (!origem || !dest) {
        cout << "Source or destination vertex not found!" << endl;
        return;
    }

    for (Vertex *v : g->getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
        v->setDist(INT_MAX);
    }
    origem->setDist(0);

    MutablePriorityQueue<Vertex> queue;
    for (Vertex *v : g->getVertexSet()) {
        queue.insert(v);
    }

    while (!queue.empty()) {
        Vertex *min = queue.extractMin();
        for (Edge *edge : min->getAdj()) {
            if (relax(edge)) {
                queue.decreaseKey(edge->getDest());
            }
        }
    }

    // Print the shortest path
    if (dest->getDist() == INT_MAX) {
        cout << "No path found from " << origin << " to " << destination << " by driving." << endl;
        return;
    }

    cout << "Shortest driving time: " << dest->getDist() << " minutes." << endl;
    cout << "Path: ";

    vector<Edge *> shortestPathEdges;
    vector<int> path;
    Vertex *current = dest;

    while (current != nullptr) {
        path.push_back(current->getId());
        if (current->getPath() != nullptr) {
            shortestPathEdges.push_back(current->getPath());  // Store edges in shortest path
            current = current->getPath()->getOrig();
        } else {
            break;
        }
    }

    // Print the path in correct order
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;

    // ========= FINDING ALTERNATIVE ROUTE =========
    double bestAlternative = INT_MAX;
    vector<int> bestAlternativePath;

    for (Edge *edge : shortestPathEdges) {
        Vertex *src = edge->getOrig();
        Vertex *dest = edge->getDest();
        double originalWeight = edge->getWeightDriving();

        // Remove the edge temporarily
        src->removeEdge(dest->getId());

        // Run Dijkstra again
        for (Vertex *v : g->getVertexSet()) {
            v->setVisited(false);
            v->setPath(nullptr);
            v->setDist(INT_MAX);
        }
        origem->setDist(0);

        MutablePriorityQueue<Vertex> queue;
        for (Vertex *v : g->getVertexSet()) {
            queue.insert(v);
        }

        while (!queue.empty()) {
            Vertex *min = queue.extractMin();
            for (Edge *edge : min->getAdj()) {
                if (relax(edge)) {
                    queue.decreaseKey(edge->getDest());
                }
            }
        }

        if (dest->getDist() != INT_MAX && dest->getDist() > shortestPathEdges.front()->getWeightDriving() && dest->getDist() < bestAlternative && dest->getId()==destination) {
            bestAlternative = dest->getDist();

            bestAlternativePath.clear();
            Vertex *altCurrent = dest;
            while (altCurrent != nullptr) {
                bestAlternativePath.push_back(altCurrent->getId());
                if (altCurrent->getPath() != nullptr) {
                    altCurrent = altCurrent->getPath()->getOrig();
                } else {
                    break;
                }
            }
        }

        // Restore the edge
        src->addEdge(dest, originalWeight, edge->getWeightWalking());
    }

    // Print the best alternative path
    if (bestAlternative == INT_MAX) {
        cout << "No alternative route found." << endl;
    } else {
        cout << "Best alternative driving time: " << bestAlternative << " minutes." << endl;
        cout << "Alternative Path: ";
        for (int i = bestAlternativePath.size() - 1; i >= 0; i--) {
            cout << bestAlternativePath[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
    }
}