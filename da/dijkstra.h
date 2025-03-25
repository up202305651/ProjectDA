//
// Created by tomas on 21-03-2025.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H


void dijkstraDriving(Graph *g, int origin);
void displayFirst(Graph *g, int origin,int destination);
void displayTwo(Graph *g, int origin, int destination, const vector<int>& nodesToAvoid, const vector<pair<int, int>>& edgesToAvoid, int includeVertex);


#endif //DIJKSTRA_H
