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

    Batch batch = new Batch();
    batch.setGraph(graph);
    batch.loadFromFile("input.txt");

    int Source_output, Destination_output;
    vector<int> DrivingRoute1;
    int TimeDrivingRoute1;
    int ParkingNode1;
    vector<int> WalkingRoute1;
    int TimeWalkingRoute1;
    int TotalTime1;
    vector<int> DrivingRoute2;
    int TimeDrivingRoute2;
    int ParkingNode2;
    vector<int> WalkingRoute2;
    int TimeWalkingRoute2;
    int TotalTime2;





    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.