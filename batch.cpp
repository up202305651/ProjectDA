//
// Created by Dival on 19/03/2025.
//
#include "graph.h"
#include "dijkstra-restricted.h"
#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "batch.h"

bool batch() {
    string line;
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "Unable to open file";
        return 1;
    }

    string Mode;
    int Source = 0, Destination = 0, MaxWalkTime = 0;
    vector<int> AvoidNodes;
    vector<Edge> AvoidSegments;
    int IncludeNode = -1;

    regex modeRegex("^Mode\\s*:\\s*([a-zA-Z-]+)\\s*$");
    regex sourceRegex("^Source\\s*:\\s*(\\d+)\\s*$");
    regex destinationRegex("^Destination\\s*:\\s*(\\d+)\\s*$");
    regex avoidNodesRegex("^AvoidNodes\\s*:\\s*([\\d,\\s]*)\\s*$");
    regex avoidSegmentsRegex("^AvoidSegments\\s*:\\s*((?:\\(\\s*\\d+\\s*,\\s*\\d+\\s*\\)\\s*(?:,\\s*)?)*)\\s*$");
    regex includeNodeRegex("^IncludeNode\\s*:?\\s*(\\d*)\\s*$");

    smatch match;
    while(getline(file, line)) {
        if (regex_match(line, match, modeRegex)) {
            Mode = match[1];
            cout << "Mode: " << Mode << endl;
        }
        else if (regex_match(line, match, sourceRegex)) {
            Source = stoi(match[1]);
            cout << "Source: " << Source << endl;
        }
        else if (regex_match(line, match, destinationRegex)) {
            Destination = stoi(match[1]);
            cout << "Destination: " << Destination << endl;
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
                        AvoidNodes.push_back(stoi(token));
                }
            }
            cout << "AvoidNodes:";
            for (int n : AvoidNodes)
                cout << " " << n;
            cout << endl;
        }
        else if (regex_match(line, match, avoidSegmentsRegex)) {
            string segStr = match[1];
            // Usar outra regex para extrair cada par dentro dos parênteses:
            regex segPairRegex("\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\)");
            auto segBegin = sregex_iterator(segStr.begin(), segStr.end(), segPairRegex);
            auto segEnd = sregex_iterator();
            for (auto it = segBegin; it != segEnd; ++it) {
                int first = stoi((*it)[1]);
                int second = stoi((*it)[2]);
                AvoidSegments.push_back(Edge(0, 0, first, second));
            }
            cout << "AvoidSegments:";
            for (const auto& seg : AvoidSegments)
                cout << " (" << seg.getOrig() << "," << seg.getDest() << ")";
            cout << endl;
        }
        else if (regex_match(line, match, includeNodeRegex)) {
            string inc = match[1];
            if (!inc.empty())
                IncludeNode = stoi(inc);
            cout << "IncludeNode: " << (IncludeNode == -1 ? "não definido" : to_string(IncludeNode)) << endl;
        }
        else {
            cout << "Linha não reconhecida: " << line << endl;
        }
    }
    return true;
}