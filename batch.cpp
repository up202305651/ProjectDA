#include "batch.h"
#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

bool batch(Graph* graph,
           std::string* Mode,
           Vertex*& Source,          // Corrigido para referência
           Vertex*& Destination,     // Corrigido para referência
           double* MaxWalkTime,
           std::vector<Vertex*>& AvoidNodes, // Corrigido para referência
           std::vector<Edge*>& AvoidSegments, // Corrigido para referência
           Vertex*& IncludeNode) {
    string line;
    ifstream file("C:/Users/Dival/Documents/Universidade/2ANO/2_SEM/DA/Project_git/input.txt");
    if (!file.is_open()) {
        cout << "Unable to open file";
        return false;
    }

    regex modeRegex("^Mode\\s*:\\s*([a-zA-Z-]+)\\s*$");
    regex sourceRegex("^Source\\s*:\\s*(\\d+)\\s*$");
    regex destinationRegex("^Destination\\s*:\\s*(\\d+)\\s*$");
    regex avoidNodesRegex("^AvoidNodes\\s*:\\s*([\\d,\\s]*)\\s*$");
    regex avoidSegmentsRegex("^AvoidSegments\\s*:\\s*((?:\\(\\s*\\d+\\s*,\\s*\\d+\\s*\\)\\s*(?:,\\s*)?)*)\\s*$");
    regex includeNodeRegex("^IncludeNode\\s*:?\\s*(\\d*)\\s*$");
    regex maxWalkTimeRegex("^MaxWalkTime\\s*:\\s*(\\d+\\.?\\d*)\\s*$");

    smatch match;
    while(getline(file, line)) {
        if (regex_match(line, match, modeRegex)) {
            *Mode = match[1];
            cout << "Mode: " << *Mode << endl;
        }
        else if (regex_match(line, match, sourceRegex)) {
            Source = graph->findVertex(stoi(match[1]));
            cout << "Source: " << Source->getId() << endl;
        }
        else if (regex_match(line, match, maxWalkTimeRegex)) {
            *MaxWalkTime = stod(match[1]);
            cout << "MaxWalkTime: " << *MaxWalkTime << endl;
        }
        else if (regex_match(line, match, destinationRegex)) {
            Destination = graph->findVertex(stoi(match[1]));
            cout << "Destination: " << Destination->getId() << endl;
        }
        else if (regex_match(line, match, avoidNodesRegex)) {
            string nodesStr = match[1];
            // Se a string não estiver vazia, separar por vírgula:
            if (!nodesStr.empty()) {
                stringstream ss(nodesStr);
                string token;
                while(getline(ss, token, ',')) {
                    // Remover espaços:
                    token.erase(0, token.find_first_not_of(" \t"));
                    token.erase(token.find_last_not_of(" \t") + 1);
                    if (!token.empty())
                        AvoidNodes.push_back(graph->findVertex(stoi(token)));
                }
            }
            cout << "AvoidNodes:";
            for (Vertex* n : AvoidNodes)
                cout << " " << n->getId();
            cout << endl;
        }
        else if (regex_match(line, match, avoidSegmentsRegex)) {
            string segStr = match[1];
            // Usar outra regex para extrair cada par dentro dos parênteses:
            regex segPairRegex("\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\)");
            auto segBegin = sregex_iterator(segStr.begin(), segStr.end(), segPairRegex);
            auto segEnd = sregex_iterator();
            for (auto it = segBegin; it != segEnd; ++it) {
                Vertex* temp_source =  graph->findVertex(stoi((*it)[1]));
                Vertex* temp_target = graph->findVertex(stoi((*it)[2]));
                Edge* existingEdge = nullptr;
                for (Edge* edge : temp_source->getAdj()) {
                    if (edge->getDest() == temp_target) { // Se o destino da aresta for o temp_target
                       existingEdge = edge;
                       break;
                    }
                }
                AvoidSegments.push_back(existingEdge);
            }
            cout << "AvoidSegments:";
            for (Edge* seg : AvoidSegments)
                cout << " (" << seg->getOrig() << "," << seg->getDest() << ")";
            cout << endl;
        }
        else if (regex_match(line, match, includeNodeRegex)) {
            string inc = match[1];
            if (!inc.empty())
                IncludeNode = graph->findVertex(stoi(inc));
            cout << "IncludeNode: " << IncludeNode->getId() << endl;
        }
        else {
            cout << "Linha não reconhecida: " << line << endl;
        }
    }
    return true;
}