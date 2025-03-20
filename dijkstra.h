#ifndef DIJKSTRA_H
#define DIJKSTRA_H

class dijkstra {
public:
    void dijkstraDriving(Graph *g, const int &origin, const int &destination) const;
    static bool relax(Edge *edge);
};

#endif //DIJKSTRA_H