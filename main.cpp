#include "graph.h"
#include <iostream>
#include "dijkstra.h"

int main() {
    Graph graph;

    // Load data from CSV files
    graph.loadLocations("/home/tomas/CLionProjects/untitled/Locations(1).csv");
    graph.loadDistances("/home/tomas/CLionProjects/untitled/Distances(1).csv");

    // Print the loaded graph to verify data
    graph.printGraph();


    int source, destination;
    cout << "Enter source node ID: ";
    cin >> source;
    cout << "Enter destination node ID: ";
    cin >> destination;

    // Run Dijkstra's algorithm
    cout << "\nCalculating shortest path..." << endl;
    /*graph.dijkstraWalking(source, destination);*/
    dijkstraDriving( &graph, source, destination);

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.