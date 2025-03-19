bool relax(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDist() + edge->getWeight() < edge->getDest()->getDist()) {
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWeight());
        edge->getDest()->setPath(edge);
        return true;
    }
    return false;
}

template <class T>
void dijkstra(Graph<T> * g, const int &origin) {
    Vertex<T> *origem = g->findVertex(origin);

    int maxi = INT_MAX;
    for ( Vertex<T> *v : g->getVertexSet() ) {
        v->setVisited(false);
        v->setPath(nullptr);
        v->setDist(maxi);
    }
    origem->setDist(0);

    MutablePriorityQueue<Vertex<T>> queue;
    for (Vertex<T> *v : g->getVertexSet()) {
        queue.insert(v);
    }

    while (!queue.empty()) {
        Vertex<T> *min = queue.extractMin();

        for (Edge<T> *edgee : min->getAdj()) {
            Vertex<T> *destino = edgee->getDest();
            if ( relax(edgee) ) {
                queue.decreaseKey(destino);
            }
        }
    }
}