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

    // ===== DIJKSTRA FOR DRIVING =====
    for (Vertex* v : g->getVertexSet()) {
        v->setDist(numeric_limits<double>::infinity());
        v->setPath(nullptr);
    }
    sourceVertex->setDist(0);

    MutablePriorityQueue<Vertex> pq;
    pq.insert(sourceVertex);

    while (!pq.empty()) {
        Vertex* u = pq.extractMin();

        for (Edge* edge : u->getAdj()) {
            Vertex* v = edge->getDest();
            double weight = edge->getWeightDriving();

            if (weight == numeric_limits<double>::infinity()) {
                continue; // No driving access
            }

            double newDist = u->getDist() + weight;
            if (newDist < v->getDist()) {
                v->setDist(newDist);
                v->setPath(edge);

                if (v->queueIndex != 0) {
                    pq.decreaseKey(v);
                } else {
                    pq.insert(v);
                }
            }
        }
    }

    // ===== FIND BEST PARKING SPOTS AND CORRESPONDING WALKING DISTANCES =====
    double bestTotalTime = numeric_limits<double>::infinity();
    Vertex* bestParkingVertex = nullptr;
    double bestDriveTime = 0;
    double bestWalkTime = 0;

    for (Vertex* parkingVertex : g->getVertexSet()) {
        if (parkingVertex->hasParking() == 0) continue;

        double driveTime = parkingVertex->getDist();
        if (driveTime == numeric_limits<double>::infinity()) continue; // unreachable parking spot

        // save driving path and time before resetting for walking processing
        double currentDriveTime = driveTime;

        // run dijkstra for walking from this parking spot
        for (Vertex* v : g->getVertexSet()) {
            v->setDist(numeric_limits<double>::infinity());
            v->setPath(nullptr);
        }
        parkingVertex->setDist(0);

        MutablePriorityQueue<Vertex> pqWalk;
        pqWalk.insert(parkingVertex);

        while (!pqWalk.empty()) {
            Vertex* u = pqWalk.extractMin();

            for (Edge* edge : u->getAdj()) {
                Vertex* v = edge->getDest();
                double weight = edge->getWeightWalking();

                if (weight == numeric_limits<double>::infinity()) continue; // No walking access

                double newDist = u->getDist() + weight;
                if (newDist < v->getDist()) {
                    v->setDist(newDist);
                    v->setPath(edge);

                    if (v->queueIndex != 0) {
                        pqWalk.decreaseKey(v);
                    } else {
                        pqWalk.insert(v);
                    }
                }
            }
        }

        double walkTime = destVertex->getDist(); // walking time from parking to destination
        if (walkTime == numeric_limits<double>::infinity()) continue;

        if (walkTime <= maxWalkingTime) { // valid route
            double totalTime = currentDriveTime + walkTime;
            // first priority: shortest total time
            // second priority: maximum driving time when total times are equal

            if ((totalTime < bestTotalTime) ||
                (totalTime == bestTotalTime &&
                walkTime > bestWalkTime)) {
                bestTotalTime = totalTime;
                bestParkingVertex = parkingVertex;
                bestDriveTime = currentDriveTime;
                bestWalkTime = walkTime;
                bestWalkTime = walkTime;
            }
        }
    }

    // ===== BEST RESULT FOUND =====
    if (!bestParkingVertex) {
        cout << "No valid route found within the given walking time limit." << endl;
        return;
    }

    // reconstruct driving path
    vector<int> drivingPath;
    for (Vertex* v : g->getVertexSet()) {
        v->setDist(numeric_limits<double>::infinity());
        v->setPath(nullptr);
    }
    sourceVertex->setDist(0);

    pq = MutablePriorityQueue<Vertex>();
    pq.insert(sourceVertex);

    while (!pq.empty()) {
        Vertex* u = pq.extractMin();

        if (u->getId() == bestParkingVertex->getId()) break;

        for (Edge* edge : u->getAdj()) {
            Vertex* v = edge->getDest();
            double weight = edge->getWeightDriving();

            if (weight == numeric_limits<double>::infinity()) continue;

            double newDist = u->getDist() + weight;
            if (newDist < v->getDist()) {
                v->setDist(newDist);
                v->setPath(edge);

                if (v->queueIndex != 0) {
                    pq.decreaseKey(v);
                } else {
                    pq.insert(v);
                }
            }
        }
    }

    Vertex* curr = bestParkingVertex;
    while (curr) {
        drivingPath.push_back(curr->getId());
        curr = curr->getPath() ? curr->getPath()->getOrig() : nullptr;
    }
    reverse(drivingPath.begin(), drivingPath.end());

    vector<int> walkingPath;

    // reconstruct walking path
    for (Vertex* v : g->getVertexSet()) {
        v->setDist(numeric_limits<double>::infinity());
        v->setPath(nullptr);
    }
    bestParkingVertex->setDist(0);

    pq = MutablePriorityQueue<Vertex>();
    pq.insert(bestParkingVertex);

    while (!pq.empty()) {
        Vertex* u = pq.extractMin();

        if (u->getId() == destVertex->getId()) break;

        for (Edge* edge : u->getAdj()) {
            Vertex* v = edge->getDest();
            double weight = edge->getWeightWalking();

            if (weight == numeric_limits<double>::infinity()) continue;

            double newDist = u->getDist() + weight;
            if (newDist < v->getDist()) {
                v->setDist(newDist);
                v->setPath(edge);

                if (v->queueIndex != 0) {
                    pq.decreaseKey(v);
                } else {
                    pq.insert(v);
                }
            }
        }
    }

    curr = destVertex;
    while (curr) {
        walkingPath.push_back(curr->getId());
        curr = curr->getPath() ? curr->getPath()->getOrig() : nullptr;
    }
    reverse(walkingPath.begin(), walkingPath.end());

    cout << "Source: " << src << endl;
    cout << "Destination: " << dest << endl;
    cout << "DrivingRoute: ";
    for (size_t i = 0; i < drivingPath.size(); i++) {
        cout << drivingPath[i];
        if (i < drivingPath.size() - 1) cout << ",";
    }
    cout << "(" << bestDriveTime << ")" << endl;
    cout << "ParkingNode: " << bestParkingVertex->getId() << endl;
    cout << "WalkingRoute: ";
    for (size_t i = 0; i < walkingPath.size(); i++) {
        cout << walkingPath[i];
        if (i < walkingPath.size() - 1) cout << ",";
    }
    cout << "(" << bestWalkTime << ")" << endl;
    cout << "TotalTime: " << bestTotalTime << endl;
}