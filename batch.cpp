#include "graph.h"
#include "dijkstra.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void batchMode() {
    ifstream inputFile("/home/tomas/CLionProjects/da/input.txt");
    ofstream outputFile("/home/tomas/CLionProjects/da/output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error: Could not open input.txt or output.txt" << endl;
        return;
    }

    string mode;
    getline(inputFile, mode, ':');  // Read 'Mode:' line
    inputFile >> mode;
    inputFile.ignore();  // Skip the remaining newline character after reading the mode

    Graph graph;
    graph.loadLocations("/home/tomas/CLionProjects/da/Locations(1).csv");
    graph.loadDistances("/home/tomas/CLionProjects/da/Distances(1).csv");

    if (mode == "driving") {
        cout << "Mode: " << mode << endl;
        int source, destination;
        vector<int> nodesToAvoid;
        vector<pair<int, int>> edgesToAvoid;
        int includeNode = -1;

        string line;

        // Read source
        getline(inputFile, line);
        stringstream ssSource(line);
        ssSource.ignore(100, ':');  // Ignore "Source:"
        ssSource >> source;
        cout << "Source: " << source << endl;

        // Read destination
        getline(inputFile, line);
        stringstream ssDestination(line);
        ssDestination.ignore(100, ':');  // Ignore "Destination:"
        ssDestination >> destination;
        cout << "Destination: " << destination << endl;

        // Read AvoidNodes
        if (getline(inputFile, line) && line.find("AvoidNodes:") != string::npos) {
            stringstream ssNodes(line.substr(line.find(":") + 1));
            int node;
            while (ssNodes >> node) {
                nodesToAvoid.push_back(node);
            }
        }

        // Read AvoidSegments
        if (getline(inputFile, line) && line.find("AvoidSegments:") != string::npos) {
            stringstream ssSegments(line.substr(line.find(":") + 1));
            int from, to;
            while (ssSegments >> from >> to) {
                edgesToAvoid.emplace_back(from, to);
            }
        }

        // Read IncludeNode
        if (getline(inputFile, line) && line.find("IncludeNode:") != string::npos) {
            stringstream ssInclude(line.substr(line.find(":") + 1));
            ssInclude >> includeNode;
        }

        // Perform the Dijkstra algorithm for driving mode
        dijkstraDriving(&graph, source);

        // Handle case when no constraints are specified
        if (nodesToAvoid.empty() && edgesToAvoid.empty() && includeNode == -1) {
            cout << "Ainda não implementei" << endl;
            // Placeholder for handling the normal case (no constraints)
            // dijkstraDriving(&graph, source);
            // displayFirstFile(&graph, source, destination, outputFile);
        } else {
            dijkstraDriving(&graph, source);
            displayTwoFile(&graph, source, destination, nodesToAvoid, edgesToAvoid, includeNode, outputFile);
        }
    } else {
        outputFile << "Invalid mode specified in input.txt" << endl;
    }

    inputFile.close();
    outputFile.close();
}
