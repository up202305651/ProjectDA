//
// Created by tomas on 19-03-2025.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H



class dijkstra {
    void dijkstraDriving(Graph *g, const int &origin, const int &destination) const;
    bool relax(Edge *edge);
};



#endif //DIJKSTRA_H
