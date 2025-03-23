#include "dijkstra-sustainable.h"

#include <algorithm>

#include "graph.h"

#include <iostream>
#include <limits.h>
#include <vector>
#include <unordered_map>
#include <limits>
#include "MutablePriorityQueue.h"

using namespace std;

bool relax(Edge* edge);

void dijkstraDrivingWalking(Graph* g, const int& src, const int& dest, int maxWalkingTime) {
    Vertex* sourceVertex = g->findVertex(src);
    Vertex* destVertex = g->findVertex(dest);

    if (!sourceVertex || !destVertex) {
      cout << "Source or destination vertex not found!" << endl;
      return;
    }

    unordered_map<int, double> drivingDist;
    unordered_map<int, double> walkingDist;
    unordered_map<int, int> bestParking;

    // ===== DIJKSTRA FOR DRIVING =====
    for (Vertex* v : g->getVertexSet()) {
        drivingDist[v->getId()] = INT_MAX;
        v->setDist(INT_MAX);
        v->setPath(nullptr);
    }
    sourceVertex->setDist(0);
    drivingDist[src] = 0;

    MutablePriorityQueue<Vertex> pq;
    pq.insert(sourceVertex);

    while (!pq.empty()) {
        Vertex* u = pq.extractMin();

        for (Edge* edge : u->getAdj()) {
            Vertex* v = edge->getDest();
            double weight = edge->getWeightDriving();

            if (weight == INT_MAX) continue; // No driving access

            if (relax(edge)) {
                pq.insert(v);
            }
        }
    }

    // ===== FIND BEST PARKING SPOTS AND CORRESPONDING WALKING DISTANCES =====
    double bestTotalTime = INT_MAX;
    int bestParkingNode = -1;
    vector<int> bestDrivingPath, bestWalkingPath;

    for (Vertex* parkingVertex : g->getVertexSet()) {
        if (parkingVertex->hasParking() == 0) continue;

        int parkingId = parkingVertex->getId();
        double driveTime = drivingDist[parkingId];

        if (driveTime == INT_MAX) continue; // unreachable parking spot

        // reset walking distances
        for (Vertex* v : g->getVertexSet()) {
            walkingDist[v->getId()] = INT_MAX;
            v->setDist(INT_MAX);
            v->setPath(nullptr);
        }
        parkingVertex->setDist(0);
        walkingDist[parkingId] = 0;

        MutablePriorityQueue<Vertex> pqWalk;
        pqWalk.insert(parkingVertex);

        while (!pqWalk.empty()) {
            Vertex* u = pqWalk.extractMin();

            for (Edge* edge : u->getAdj()) {
                Vertex* v = edge->getDest();
                double weight = edge->getWeightWalking();
                if (weight == INT_MAX) continue; // No walking access

                if (relax(edge)) {
                    pqWalk.insert(v);
                }
          }
        }

        double walkingTime = walkingDist[dest]; // walking time from parking to destination
        if (walkingTime == INT_MAX) continue;

        if (walkingTime <= maxWalkingTime) {
            double totalTime = driveTime + walkingTime;
            // update best parking spot
            if (totalTime < bestTotalTime) {
                bestTotalTime = totalTime;
                bestParkingNode = parkingId;

                // retrieve driving path
                bestDrivingPath.clear();
                Vertex* curr = parkingVertex;
                while (curr) { // from parking to source
                    bestDrivingPath.push_back(curr->getId());
                    if (curr->getPath()) curr = curr->getPath()->getOrig();
                    else break;
                }
                reverse(bestDrivingPath.begin(), bestDrivingPath.end());

                // retrieve walking path
                bestWalkingPath.clear();
                curr = destVertex;
                while (curr) {
                    bestWalkingPath.push_back(curr->getId());
                    if (curr->getPath()) curr = curr->getPath()->getOrig();
                    else break;
                }
                reverse(bestWalkingPath.begin(), bestWalkingPath.end());
            }
        }
    }

    // ===== BEST RESULT FOUND =====
    if (bestParkingNode == -1) {
        cout << "No valid route found within the given walking time limit." << endl;
        return;
    }
    cout << "Source: " << src << endl;
    cout << "Destination: " << dest << endl;
    cout << "DrivingRoute:";
    for (size_t i = 0; i < bestDrivingPath.size(); ++i) {
        cout << bestDrivingPath[i];
        if (i < bestDrivingPath.size() - 1) cout << ",";
    }
    cout << "(" << drivingDist[bestParkingNode] << ")" << endl;
    cout << "ParkingNode:" << bestParkingNode << endl;
    cout << "WalkingRoute:";
    for (size_t i = 0; i < bestWalkingPath.size(); ++i) {
        cout << bestWalkingPath[i];
        if (i < bestWalkingPath.size() - 1) cout << ",";
    }
    cout << "(" << walkingDist[dest] << ")" << endl;
    cout << "TotalTime:" << bestTotalTime << " min" << endl;
}