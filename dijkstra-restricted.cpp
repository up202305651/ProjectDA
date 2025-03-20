#include "dijkstra-restricted.h"

#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
#include <unordered_map>
#include <limits>
#include <set>

#include "graph.h"
#include "MutablePriorityQueue.h"

using namespace std;

bool relax(Edge* edge);

void runDijkstra(Graph* g, const int& source, const int& destination) {
    Vertex* sourceVertex = g->findVertex(source);
    Vertex* destVertex = g->findVertex(destination);

    if (!sourceVertex || !destVertex) {
        cout << "Source or destination vertex not found!" << endl;
        return;
    }

    // Reset all vertices
    for (Vertex* v : g->getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
        v->setDist(INT_MAX);
    }
    sourceVertex->setDist(0);

    MutablePriorityQueue<Vertex> queue;
    for (Vertex* v : g->getVertexSet()) {
        queue.insert(v);
    }

    // Run Dijkstra's algorithm
    while (!queue.empty()) {
        Vertex* min = queue.extractMin();
        for (Edge* edge : min->getAdj()) {
            if (relax(edge)) {
                queue.decreaseKey(edge->getDest());
            }
        }
    }
}

void printPath(Vertex* dest) {
    if (dest->getDist() == INT_MAX) {
        cout << "No path found to destination." << endl;
        return;
    }

    cout << "Shortest driving time: " << dest->getDist() << " minutes." << endl;
    cout << "Path: ";

    vector<int> path;
    Vertex* current = dest;

    while (current != nullptr) {
        path.push_back(current->getId());
        if (current->getPath() != nullptr) {
            current = current->getPath()->getOrig();
        } else {
            break;
        }
    }

    // print in correct order
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

void dijkstraRestricted(Graph* g, const int& src, const int& dest,
    const vector<int>& avoidNodes, const vector<pair<int, int>>& avoidSegments,
    const int& includeNode) {
    Vertex* sourceVertex = g->findVertex(src);
    Vertex* destVertex = g->findVertex(dest);

    if (!sourceVertex || !destVertex)   {
        cout << "Source or destination vertex not found!" << endl;
        return;
    }

    // store removed edges to restore graph later
    unordered_map<int, vector<pair<int, pair<double, double>>>> removedEdges;

    for (int nodeId : avoidNodes) {
        if (nodeId == src || nodeId == dest) {
            cout << "Warning: Cannot avoid source or destination node." << endl;
            continue;
        }

        Vertex* v = g->findVertex(nodeId);
        if (v) {
            // store outgoing edges before removing
            for (Edge* edge : v->getAdj()) {
                int destId = edge->getDest()->getId();
                removedEdges[nodeId].push_back({destId, {edge->getWeightDriving(), edge->getWeightWalking()}});
            }
            v->removeOutgoingEdges();

            // remove incoming edges
            for (Vertex* other : g->getVertexSet()) {
                if (other->getId() != nodeId) {
                    if (other->removeEdge(nodeId)) {
                        // store edge info for restoration
                        removedEdges[other->getId()].push_back({nodeId, {0, 0}});
                    }
                }
            }
        }
    }

    // remove avoided segments
    for (const auto& segment : avoidSegments) {
        int srcId = segment.first;
        int destId = segment.second;

        // skip if source or destination would be isolated
        if ((srcId == src && destId == dest) ||
            (srcId == dest && destId == src)) {
            cout << "Warning: Cannot avoid direct segment between source and destination." << endl;
            continue;
        }

        Vertex* source = g->findVertex(srcId);
        if (source) {
            // store edge info before removing
            for (Edge* edge : source->getAdj()) {
                if (edge->getDest()->getId() == destId) {
                    removedEdges[srcId].push_back({destId, {edge->getWeightDriving(), edge->getWeightWalking()}});
                    break;
                }
            }
            source->removeEdge(destId);
        }
    }

    // Include node
    if (includeNode != -1 && includeNode != src && includeNode != dest) {
        Vertex* includeVertex = g->findVertex(includeNode);
        if (!includeVertex) {
            cout << "Include node not found in graph!" << endl;
        } else {
            runDijkstra(g, src, includeNode);

            if (includeVertex->getDist() == INT_MAX) {
                cout << "No path found from " << src << " to " << includeNode << " by driving." << endl;
            } else {
                double firstPartDist = includeVertex->getDist();
                vector<int> firstPart;
                Vertex* current = includeVertex;

                while (current!= nullptr) {
                    firstPart.push_back(current->getId());
                    if (current->getPath() != nullptr) {
                        current = current->getPath()->getOrig();
                    } else {
                        break;
                    }
                }

                // Include node to destination
                runDijkstra(g, includeNode, dest);

                if (destVertex->getDist() == INT_MAX) {
                    cout << "No path found from " << includeNode << " to " << dest << " by driving." << endl;
                } else {
                    cout << "Shortest path through required node " << includeNode << ":" << endl;
                    cout << "Total driving time: " << (firstPartDist + destVertex->getDist()) << " minutes." << endl;

                    cout << "Source to Include Node:" << endl;
                    for (int i = firstPart.size() - 1; i <= 0; i--) {
                        cout << firstPart[i];
                        if (i > 0) cout << " -> ";
                    }
                    cout << endl;

                    cout << "Include Node to Destination:" << endl;
                    printPath(destVertex);
                }
            }
        }
    } else {
        // Run Dijkstra's algorithm
        runDijkstra(g, src, dest);
        cout << "Restricted route from " << src << " to " << dest << ":" << endl;
        printPath(destVertex);
    }

    /* Restore original graph
    for (const auto& entry : removedEdges) {
        int srcId = entry.first;
        Vertex* srcVertex = g->findVertex(srcId);

        if (srcVertex) {
            for (const auto& destInfo : entry.second) {
                int destId = destInfo.first;
                double drivingWeight = destInfo.second.first;
                double walkingWeight = destInfo.second.second;

                Vertex* destVertex = g->findVertex(destId);
                if (destVertex && drivingWeight > 0) {
                    srcVertex->addEdge(destVertex, drivingWeight, walkingWeight);
                }
            }
        }
    }
    */
}