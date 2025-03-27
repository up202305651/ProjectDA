#include "dijkstra-sustainable.h"

#include <algorithm>

#include "graph.h"
#include <iostream>
#include <limits.h>
#include <limits>
#include <vector>
#include <unordered_map>
#include "MutablePriorityQueue.h"

using namespace std;

static const double INF = numeric_limits<double>::infinity();

void dijkstraHelper(Graph* g, int start, bool drivingMode, vector<double>& dist, vector<Edge*>& path) {
    dist.assign(g->getNumVertex(), INF);
    path.assign(g->getNumVertex(), nullptr);

    MutablePriorityQueue<Vertex> pq;

    Vertex* s = g->findVertex(start);
    if (!s) return;

    dist[s->getId() - 1] = 0.0; // start vertex has distance 0
    s->setDist(0.0);
    pq.insert(s);

    // Dijkstra's algorithm
    while (!pq.empty()) {
        Vertex* u = pq.extractMin();
        double distU = dist[u->getId() - 1];
        for (Edge* e : u->getAdj()) {
            Vertex* w = e->getDest();

            double time = drivingMode ? e->getWeightDriving() : e->getWeightWalking();
            if (time == INF) continue;

            double newDist = distU + time;
            if (newDist < dist[w->getId() - 1]) {
                dist[w->getId() - 1] = newDist;
                path[w->getId() - 1] = e; // store the edge used to reach w

                w->setDist(newDist);
                if (!pq.contains(w)) {
                    pq.insert(w);
                } else {
                    pq.decreaseKey(w);
                }
            }
        }
    }
}

void dijkstraDrivingWalking(Graph* g, const int& src, const int& dest, int maxWalkingTime) {
    Vertex* origin = g->findVertex(src);
    Vertex* destination = g->findVertex(dest);

    if (!origin || !destination) {
        cout << "Source or destination vertex not found!" << endl;
        return;
    }

    if (origin->hasParking() > 0 || destination->hasParking() > 0) {
        cout << "Origin and destination nodes must not be parking nodes." << endl;
        return;
    }

    vector<double> distDriving, distWalking;
    vector<Edge*> pathDriving, pathWalking;

    // ===== DIJKSTRA FOR DRIVING =====
    dijkstraHelper(g, src, true, distDriving, pathDriving);

    // ===== DIJKSTRA FOR WALKING =====
    dijkstraHelper(g, dest, false, distWalking, pathWalking);

    // ===== SEARCH FOR THE BEST PARKING NODE =====
    double bestTotalTime = INF;
    int bestParkingId = -1;
    double bestParkingWalkingTime = 0.0;

    for (Vertex* v : g->getVertexSet()) {
        if (v->getId() == src || v->getId() == dest) continue;
        if (v->hasParking() == 0) continue;

        double driveTime = distDriving[v->getId() - 1];
        double walkTimeFromDest = distWalking[v->getId() - 1];

        if (driveTime == INF || walkTimeFromDest == INF) continue;
        if (walkTimeFromDest > maxWalkingTime) continue;

        double totalTime = driveTime + walkTimeFromDest;

        if (totalTime < bestTotalTime) {
            bestTotalTime = totalTime;
            bestParkingId = v->getId();
            bestParkingWalkingTime = walkTimeFromDest;
        } else if (abs(totalTime -  bestTotalTime) < 1e-9) {
            // empate: escolher o que tem maior tempo de caminhada
            if (walkTimeFromDest > bestParkingWalkingTime) {
                bestParkingId = v->getId();
                bestParkingWalkingTime = walkTimeFromDest;
            }
        }
    }

    if (bestParkingId == -1) {
        cout << "No parking node found to the requirements." << endl;
        return;
    }

    vector<double> distWalkFoward;
    vector<Edge*> pathWalkFoward;
    dijkstraHelper(g, bestParkingId, false, distWalkFoward, pathWalkFoward);

    // ===== RECONSTRUCT THE ROUTE =====
    vector<int> driveRoute;
    int cur = bestParkingId;
    while (cur != src) {
        Edge* e = pathDriving[cur - 1];
        if (!e) break;
        driveRoute.push_back(cur);
        cur = e->getOrig()->getId();
    }
    driveRoute.push_back(src);
    reverse(driveRoute.begin(), driveRoute.end());

    vector<int> walkRoute;
    cur = dest;
    while (cur != bestParkingId) {
        Edge* e = pathWalkFoward[cur - 1];
        if (!e) break;
        walkRoute.push_back(cur);
        cur = e->getOrig()->getId();
    }
    walkRoute.push_back(bestParkingId);
    reverse(walkRoute.begin(), walkRoute.end());

    // ===== PRINT THE RESULT =====
    cout << "Best Parking Node = " << bestParkingId << endl;
    cout << "Total time = " << bestTotalTime << " (driving + walking)" << endl;

    // Print driving route
    cout << "Driving route: ";
    for (size_t i = 0; i < driveRoute.size(); i++) {
        cout << driveRoute[i];
        if (i + 1 < driveRoute.size()) cout << " -> ";
    }
    cout << '(' << distDriving[bestParkingId - 1] << ')';
    cout << endl;

    // Print walking route
    cout << "Walking route: ";
    for (size_t i = 0; i < walkRoute.size(); i++) {
        cout << walkRoute[i];
        if (i + 1 < walkRoute.size()) cout << " -> ";
    }
    cout << '(' << distWalking[bestParkingId - 1] << ')';
    cout << endl;
}