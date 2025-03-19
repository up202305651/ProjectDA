#include "graph.h"
#include <regex>
#include <vector>
#include <string>
#include "batch.h"

#include "batch.h"
using namespace std;
int main() {
    Graph graph;

    // Load data from CSV files
    graph.loadLocations("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/Locations.csv");
    graph.loadDistances("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/Distances.csv");

    // Print the loaded graph to verify data
    graph.printGraph();

    //preparar para a leitura
    std::string Mode; // Objeto, não ponteiro
    Vertex* Source = nullptr;
    Vertex* Destination = nullptr;
    double MaxWalkTime = 0.0; // Inicializado
    std::vector<Vertex*> AvoidNodes;
    std::vector<Edge*> AvoidSegments;
    Vertex* IncludeNode = nullptr;

    batch(&graph, &Mode, Source, Destination, &MaxWalkTime, AvoidNodes, AvoidSegments, IncludeNode);



    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.