#include "graph.h"
#include <iostream>

int main() {
    Graph graph;

    // Load data from CSV files
    graph.loadLocations("/home/tomas/CLionProjects/untitled/Locations.csv");
    graph.loadDistances("/home/tomas/CLionProjects/untitled/Distances.csv");

    // Print the loaded graph to verify data
    graph.printGraph();


    int source, destination;
    cout << "Enter source node ID: ";
    cin >> source;
    cout << "Enter destination node ID: ";
    cin >> destination;

    // Run Dijkstra's algorithm
    cout << "\nCalculating shortest path..." << endl;
    graph.dijkstraShortestPath(source, destination);

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.