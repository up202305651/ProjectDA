#include "graph.h"
#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    Graph graph;

    // Load data from CSV files
    graph.loadLocations("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/Locations.csv");
    graph.loadDistances("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/Distances.csv");

    // Print the loaded graph to verify data
    graph.printGraph();

    string line;
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "Unable to open file";
        return 1;
    }

    string Mode;
    int Source = 0, Destination = 0, MaxWalkTime = 0;
    const set<int> AvoidNodes;
    const set<pair<int, int>> AvoidSegments;
    int IncludeNode = -1;

    regex modeRegex("^Mode\\s*:\\s*([a-zA-Z-]+)\\s*$");
    regex sourceRegex("^Source\\s*:\\s*(\\d+)\\s*$");
    regex destinationRegex("^Destination\\s*:\\s*(\\d+)\\s*$");
    regex avoidNodesRegex("^AvoidNodes\\s*:\\s*([\\d,\\s]*)\\s*$");
    regex avoidSegmentsRegex("^AvoidSegments\\s*:\\s*((?:\\(\\s*\\d+\\s*,\\s*\\d+\\s*\\)\\s*(?:,\\s*)?)*)\\s*$");
    regex includeNodeRegex("^IncludeNode\\s*:?\\s*(\\d*)\\s*$");

    smatch match;
    while (getline(file, line)) {
        if (regex_match(line,match, modeRegex)) {
            Mode = match[1];
            cout << "Mode: " << Mode << endl;
        }
        else if {}

    }

    dijkstraRestricted(graph, Source, Destination, AvoidNodes, AvoidSegments, IncludeNode);
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.