#include "graph.h"
#include <iostream>
#include "batch.h"
#include "dijkstra.h"


void manualMode() {
    Graph graph;
    int mode;

        cout << "\n=== Select the Mode ===\n";
        cout << "1 - Independent Route Planning\n";
        cout << "2 - Restricted Route Planning\n";
        cout << "0 - Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> mode;

        if (mode == 0) {
            cout << "\nReturning to Main Menu...\n";
        }
        else if (mode == 1) {
            Graph graph;
            graph.loadLocations("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/da/Locations(1).csv");
            graph.loadDistances("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/da/Distances(1).csv");
            // Independent Route Planning
            int source, destination;
            cout << "\n=== Independent Route Planning ===\n";
            cout << "Enter source node ID: ";
            cin >> source;
            cout << "Enter destination node ID: ";
            cin >> destination;

            cout << "\nCalculating independent route...\n";
            // CALL YOUR FUNCTION HERE (Independent Route)

            dijkstraDriving( &graph, source);
            displayFirst(&graph, source, destination);
            dijkstraDriving(&graph, source);
            displayFirst(&graph, source, destination);
        }
        else if (mode == 2) {
            Graph graph;
            graph.loadLocations("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/da/Locations(1).csv");
            graph.loadDistances("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/da/Distances(1).csv");
            // Restricted Route Planning
            int source, destination, includeNode;
            vector<int> nodesToAvoid;
            vector<pair<int, int>> edgesToAvoid;

            cout << "\n=== Restricted Route Planning ===\n";
            cout << "Enter source node ID: ";
            cin >> source;
            cout << "Enter destination node ID: ";
            cin >> destination;

            // Receiving nodes to avoid
            cout << "Enter nodes to avoid (end with -1): ";
            int node;
            while (cin >> node && node != -1) {
                nodesToAvoid.push_back(node);
            }

            // Receiving edges to avoid
            cout << "Enter edges to avoid in format 'from to' (end with -1 -1): ";
            int from, to;
            while (cin >> from >> to && (from != -1 || to != -1)) {
                edgesToAvoid.push_back({from, to});
            }

            // Receiving mandatory node to include
            cout << "Enter node ID to include (-1 if none): ";
            cin >> includeNode;

            cout << "\nCalculating restricted route...\n";
            // CALL YOUR FUNCTION HERE (Restricted Route)
            dijkstraDriving(&graph, destination);
            displayTwo(&graph, source,destination, nodesToAvoid, edgesToAvoid, includeNode);
        }
        else if (mode == 3) {
            cout << "\nNot implemented yet...\n";
        }
        else if (mode == 4) {
            cout << "\nNot implemented yet...\n";
        }
        else {
            cout << "\nInvalid choice. Please enter 1, 2, or 0.\n";
        }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(){
    int choice;
    cout << "Select mode:\n";
    cout << "1 - Batch Mode\n";
    cout << "2 - Manual Mode\n";
     cout << "0 - Exit\n";
     cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 0) {
        cout << "Exiting program...\n";
    }
    else if (choice == 1) {
        cout<<"\n Batch mode :)\n";
        /*batchMode();*/
        Graph graph;
        graph.loadLocations("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/da/Locations(1).csv");
        graph.loadDistances("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/da/Distances(1).csv");

        Batch batch(&graph);

        batch.loadFromFile("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/da/input.txt");


        std::vector<int> nodeIds;
        for (Vertex* vertex : batch.getAvoidNodes()) {
            nodeIds.push_back(vertex->getId());
        }
        nodeIds.push_back(-1);

        std::vector<std::pair<int, int>> segmentIds;
        for (Edge* edge : batch.getAvoidSegments()) {
            int sourceId = edge->getOrig()->getId();
            int destId = edge->getDest()->getId();
            segmentIds.emplace_back(sourceId, destId);
        }
        segmentIds.emplace_back(-1, -1);


        dijkstraDriving(&graph, batch.getSource()->getId());
        displayFirst(&graph, batch.getSource()->getId(), batch.getDestination()->getId());

        dijkstraDriving(&graph, batch.getSource()->getId());
        displayFirst(&graph, batch.getSource()->getId(), batch.getDestination()->getId());



    }
    else if (choice == 2) {
        manualMode();
    }
    else {
        cout << "Invalid choice. Please enter 1, 2, or 0.\n";
    }

    return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.