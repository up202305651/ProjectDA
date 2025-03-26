#include <algorithm>
#include "graph.h"
#include "dijkstra.h"
#include <limits.h>
#include <vector>

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


void dijkstraDriving(Graph *g,  int origin) {
    Vertex *origem = g->findVertex(origin);

    int maxi = INT_MAX;
    for ( Vertex *v : g->getVertexSet() ) {
        if (!v->getAvoidVertex()) {
            v->setVisited(false);
            v->setPath(nullptr);
            v->setDist(maxi);
        }
    }
    origem->setDist(0);

    MutablePriorityQueue<Vertex> queue;
    for (Vertex *v : g->getVertexSet()) {
        if (!v->getAvoidVertex())
            queue.insert(v);
    }

    while (!queue.empty()) {
        Vertex*min = queue.extractMin();

        for (Edge *edgee : min->getAdj()) {
            Vertex *destino = edgee->getDest();
            if ( !edgee->getAvoidEdge() && relax(edgee) ) {
                queue.decreaseKey(destino);
            }
        }
    }
}

void displayFirst(Graph *g, int origin, int destination) {
    Vertex *destino = g->findVertex(destination);
    if (destino->getDist() == INT_MAX) {
        cout << "No path found from " << origin << " to " << destination << endl;
        return;
    }

    // Print shortest path
    vector<int> path;
    double totalWeight = destino->getDist();
    Vertex *current = destino;

    while (current != nullptr && current->getId() != origin) {
        path.push_back(current->getId());

        Edge *edge = current->getPath();
        if (edge != nullptr) {
            Vertex *prev = edge->getOrig();
            if (prev->getId() != origin && prev->getId() != destination) {
                prev->setAvoidVertex(true);  // Mark vertex as avoided
            }
            edge->setAvoidEdge(true); // Mark edge as avoided
        }

        current = edge ? edge->getOrig() : nullptr;
    }
    path.push_back(origin);
    reverse(path.begin(), path.end());

    // Output result
    cout << "\n Display : \n";
    cout << "Shortest Path: ";
    for (int id : path) cout << id << " ";
    cout << "\nTotal Weight: " << totalWeight << endl;
}

void displayTwo(Graph *g, int origin, int destination, const vector<int>& nodesToAvoid,
                const vector<pair<int, int>>& edgesToAvoid, int includeVertex) {
    // Marcar os nós para evitar
    for (int nodeId : nodesToAvoid) {
        Vertex *v = g->findVertex(nodeId);
        if (v) v->setAvoidVertex(true);
    }

    // Marcar os segmentos para evitar
    for (const auto& edgePair : edgesToAvoid) {
        Vertex *v = g->findVertex(edgePair.first);
        if (v) {
            for (Edge *e : v->getAdj()) {
                if (e->getDest()->getId() == edgePair.second) {
                    e->setAvoidEdge(true);
                }
            }
        }
    }

    double totalWeight = 0;  // Variável para armazenar o peso total do caminho

    // **Caso não haja um nó obrigatório, executamos um único Dijkstra**
    if (includeVertex == -1 || includeVertex == origin || includeVertex == destination) {
        dijkstraDriving(g, origin);
        Vertex *destino = g->findVertex(destination);
        if (!destino || destino->getDist() == INT_MAX) {
            cout << "No path found from " << origin << " to " << destination << endl;
            return;
        }
        vector<int> path;
        totalWeight = destino->getDist();
        Vertex *current = destino;

        while (current != nullptr && current->getId() != origin) {
            path.push_back(current->getId());
            current = current->getPath() ? current->getPath()->getOrig() : nullptr;
        }
        path.push_back(origin);
        reverse(path.begin(), path.end());

        // **Print the result**
        cout << "Best Path: ";
        for (int id : path) cout << id << " ";
        cout << "\nTotal Weight: " << totalWeight << " minutes" << endl;

        return;
    }
    else {
        // **Dijkstra do source até o includeVertex**
        dijkstraDriving(g, origin);
        Vertex *midpoint = g->findVertex(includeVertex);
        if (!midpoint || midpoint->getDist() == INT_MAX) {
            cout << "No path found from " << origin << " to required node " << includeVertex << endl;
            return;
        }

        // **Guardar o primeiro caminho e peso**
        vector<int> firstPath;
        double weight1 = midpoint->getDist();
        Vertex *current = midpoint;
        while (current != nullptr && current->getId() != origin) {
            firstPath.push_back(current->getId());
            current = current->getPath() ? current->getPath()->getOrig() : nullptr;
        }
        firstPath.push_back(origin);
        reverse(firstPath.begin(), firstPath.end());

        // **Dijkstra do includeVertex até o destination**
        dijkstraDriving(g, includeVertex);
        Vertex *destino = g->findVertex(destination);
        if (!destino || destino->getDist() == INT_MAX) {
            cout << "No path found from required node " << includeVertex << " to " << destination << endl;
            return;
        }

        // **Guardar o segundo caminho e peso**
        vector<int> secondPath;
        double weight2 = destino->getDist();
        current = destino;
        while (current != nullptr && current->getId() != includeVertex) {
            secondPath.push_back(current->getId());
            current = current->getPath() ? current->getPath()->getOrig() : nullptr;
        }

        // **Calcular peso total**
        totalWeight = weight1 + weight2;

        // **Combinar os caminhos**
        firstPath.insert(firstPath.end(), secondPath.rbegin(), secondPath.rend());

        // **Imprimir resultado**
        cout << "Best Path: ";
        for (int id : firstPath) cout << id << " ";
    }

    // **Imprimir peso total corretamente**
    cout << "\nTotal Weight: " << totalWeight << " minutes" << endl;
}
