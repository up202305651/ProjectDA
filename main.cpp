#include "graph.h"
#include <iostream>
#include "dijkstra.h"

int main() {
    Graph graph;

    // Load data from CSV files
    graph.loadLocations("/home/bia/Documents/feup/DA/ProjectDA/Locations.csv");
    graph.loadDistances("/home/bia/Documents/feup/DA/ProjectDA/Distances.csv");

    // Print the loaded graph to verify data
    graph.printGraph();


    int source, destination;
    vector<int> avoidNodes;
    vector<pair<int, int>> avoidSegments;
    int includeNode;
    cout << "Enter source node ID: ";
    cin >> source;
    cout << "Enter destination node ID: ";
    cin >> destination;
    cout << "Enter avoid nodes (0 to stop): ";
    int avoidNode;
    while (cin >> avoidNode && avoidNode != 0) {
        avoidNodes.push_back(avoidNode);
    }
    cout << "Enter avoid segments (0 0 to stop): ";
    int src, dest;
    while (cin >> src >> dest && src != 0 && dest != 0) {
        avoidSegments.emplace_back(src, dest);
    }
    cout << "Enter include node ID: ";
    cin >> includeNode;

    // Run Dijkstra's algorithm
    cout << "\nCalculating shortest path..." << endl;
    /*graph.dijkstraWalking(source, destination);*/
    dijkstraDriving( &graph, source, destination);
    dijkstraRestricted(&graph, source, destination, {1, 2, 3}, {{1, 2}, {2, 3}}, 4);

    return 0;
}