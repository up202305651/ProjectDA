#include "graph.h"

#include <climits>
#include <fstream>
#include <limits>
#include <sstream>

// =================== Vertex Class ===================
Vertex::Vertex(int id,string code, int parking) : id(id), code(code), parking(parking) {}

bool Vertex::operator<(Vertex &vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return id;
}
string Vertex::getCode() const {
    return code;
}

int Vertex::hasParking() const {
    return parking;
}

vector<Edge *> Vertex::getAdj() const {
    return adj;
}

bool Vertex::isVisited() const {
    return visited;
}

bool Vertex::isProcessing() const {
    return processing;
}

unsigned int Vertex::getIndegree() const {
    return indegree;
}

double Vertex::getDist() const {
    return dist;
}

Edge *Vertex::getPath() const {
    return path;
}

vector<Edge *> Vertex::getIncoming() const {
    return incoming;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

Edge *Vertex::addEdge(Vertex *dest, double driving, double walking) {
    Edge *edge = new Edge(this, dest, driving, walking);
    adj.push_back(edge);
    dest->incoming.push_back(edge);
    return edge;
}

bool Vertex::removeEdge(int id) {
    auto it = adj.begin();
    while (it != adj.end()) {
        if ((*it)->getDest()->getId() == id) {
            delete *it;
            it = adj.erase(it);
            return true;
        } else {
            ++it;
        }
    }
    return false;
}

void Vertex::removeOutgoingEdges() {
    for (Edge *edge : adj) {
        delete edge;
    }
    adj.clear();
}

// =================== Edge Class ===================
Edge::Edge(Vertex *orig, Vertex *dest, double driving, double walking) : orig(orig), dest(dest), driving(driving), walking(walking) {}

Vertex *Edge::getDest() const {
    return dest;
}

double Edge::getWeightWalking() const {
    return walking;
}

double Edge::getWeightDriving() const {
    return driving;
}

Vertex *Edge::getOrig() const {
    return orig;
}

// =================== Graph Class ===================
Graph::~Graph() {
    for (Vertex *v : vertexSet) {
        delete v;
    }
}

Vertex *Graph::findVertex(int id) const {
    for (Vertex *v : vertexSet) {
        if (v->getId() == id)
            return v;
    }
    return nullptr;
}

bool Graph::addVertex(int id,string code,int parking) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id,code,parking));
    return true;
}

bool Graph::removeVertex(int id) {
    auto it = vertexSet.begin();
    while (it != vertexSet.end()) {
        if ((*it)->getId() == id) {
            delete *it;
            it = vertexSet.erase(it);
            return true;
        } else {
            ++it;
        }
    }
    return false;
}

bool Graph::addEdge(int src, int dest, double driving, double walking) {
    Vertex *v1 = findVertex(src);
    Vertex *v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;

    // Add edge from src to dest
    v1->addEdge(v2, driving, walking);
    // Add reverse edge from dest to src
    v2->addEdge(v1, driving, walking);

    return true;
}

bool Graph::removeEdge(int src, int dest) {
    Vertex *v = findVertex(src);
    if (v == nullptr)
        return false;
    return v->removeEdge(dest);
}

int Graph::getNumVertex() const {
    return vertexSet.size();
}

vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


void Graph::loadLocations(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        string location, code;
        int id, parking;
        stringstream ss(line);

        if (getline(ss, location, ',') && ss >> id && ss.ignore() && getline(ss, code, ',') && ss >> parking) {
            cout << "Loading Vertex: ID=" << id << ", Code=" << code << ", Parking=" << parking << endl;
            addVertex(id, code, parking);
        } else {
            cerr << "Error parsing line: " << line << endl;
        }
    }
    file.close();
}


void Graph::loadDistances(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        string code1, code2, drivingStr, walkingStr;
        double driving, walking;
        stringstream ss(line);

        if (getline(ss, code1, ',') && getline(ss, code2, ',') && getline(ss, drivingStr, ',') && getline(ss, walkingStr, ',')) {
            // Convert "X" to a very large number (or just skip adding the edge for driving)
            if (drivingStr == "X") {
                driving = INT_MAX; // No driving access
            } else {
                driving = stod(drivingStr);
            }

            walking = stod(walkingStr); // Walking is always a number

            // Find vertices by their codes
            Vertex* v1 = nullptr;
            Vertex* v2 = nullptr;

            for (Vertex* v : vertexSet) {
                if (v->getCode() == code1) v1 = v;
                if (v->getCode() == code2) v2 = v;
            }

            if (v1 && v2) {
                cout << "Adding Edge: " << code1 << " -> " << code2
                     << " (Driving: " << (driving == numeric_limits<double>::infinity() ? "N/A" : to_string(driving))
                     << ", Walking: " << walking << ")" << endl;
                if (v1 && v2) {
                    addEdge(v1->getId(), v2->getId(), driving, walking); // ✅ Use Graph::addEdge
                }
            } else {
                cerr << "Warning: Unknown location code(s) - " << code1 << ", " << code2 << endl;
            }
        } else {
            cerr << "Error parsing line: " << line << endl;
        }
    }
    file.close();
}


void Graph::printGraph() const {
    cout << "Graph Structure:" << endl;
    if (vertexSet.empty()) {
        cout << "Graph is empty!" << endl;
        return;
    }
    for (Vertex *v : vertexSet) {
        cout << "Vertex " << v->getId() << " (" << v->getCode() << ")";
        if (v->hasParking()) {
            cout << " [P]"; // Indicate parking available
        }
        cout << " -> ";
        for (Edge *e : v->getAdj()) {
            cout << e->getDest()->getId() << "(" << e->getWeightDriving() << ") "<<"(" << e->getWeightWalking() << ") ";
        }
        cout << endl;
    }
}
