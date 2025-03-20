//
// Created by tomas on 19-03-2025.
//

#ifndef DIJKSTRA_RESTRICTED_H
#define DIJKSTRA_RESTRICTED_H
#include <set>
#include "graph.h"

void dijkstraRestricted(Graph* g, const int& src, const int& dest,
    const vector<int>& avoidNodes, const vector<pair<int, int>>& avoidSegments,
    const int& includeNode);
void runDijkstra(Graph* g, const int& source, const int& destination);
void printPath(Vertex* dest);

#endif // DIJKSTRA_RESTRICTED_H