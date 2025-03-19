#include "graph.h"
#include <iostream>

int main() {
    Graph graph;

    // Load data from CSV files
    graph.loadLocations("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/Locations.csv");
    graph.loadDistances("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/Distances.csv");

    // Print the loaded graph to verify data
    graph.printGraph();

    string Mode;
    int Source, Destination, MaxWalkTime;
    vector<int> AvoidNodes;
    vector<Edge> AvoidSegments;

    ifstream file("input.txt");
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.