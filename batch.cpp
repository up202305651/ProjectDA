#include "batch.h"
#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>



bool Batch::loadFromFile(const std::string& filename) {
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
    }
    string line;
    while (std::getline(file, line)) {
        Batch::processLine(line);
    }
    file.close();
    return true;

}
void Batch::setOutputFile(string strinG) {
    std::ofstream *file(strinG);
    file_ = file;
}
std::ifstream Batch::getFile() {return file_;};
std::string Batch::getMode() const { return mode_; }
Vertex* Batch::getSource() const { return source_; }
Vertex* Batch::getDestination() const { return destination_; }
double Batch::getMaxWalkTime() const { return maxWalkTime_; }
const std::vector<Vertex*>& Batch::getAvoidNodes() const { return avoidNodes_; }
const std::vector<Edge*>& Batch::getAvoidSegments() const { return avoidSegments_; }
Vertex* Batch::getIncludeNode() const { return includeNode_; }


void Batch::processLine(const std::string& line) {
    regex modeRegex("^Mode\\s*:\\s*([a-zA-Z-]+)\\s*$");
    regex sourceRegex("^Source\\s*:\\s*(\\d+)\\s*$");
    regex destinationRegex("^Destination\\s*:\\s*(\\d+)\\s*$");
    regex avoidNodesRegex("^AvoidNodes\\s*:\\s*([\\d,\\s]*)\\s*$");
    regex avoidSegmentsRegex(R"(^AvoidSegments\s*:\s*((?:\(\s*\d+\s*,\s*\d+\s*\)\s*(?:,\s*)?)*)\s*$)");
    regex includeNodeRegex("^IncludeNode\\s*:?\\s*(\\d*)\\s*$");
    regex maxWalkTimeRegex("^MaxWalkTime\\s*:\\s*(\\d+\\.?\\d*)\\s*$");

    smatch match;
    if (regex_match(line, match, modeRegex)) {
        mode_ = match[1];
        cout << "Mode: " << mode_ << endl;
    }
    else if (regex_match(line, match, sourceRegex)) {
        source_ = graph_->findVertex(stoi(match[1]));
        cout << "Source: " << source_->getId() << endl;
    }
    else if (regex_match(line, match, maxWalkTimeRegex)) {
        maxWalkTime_ = stod(match[1]);
        cout << "MaxWalkTime: " << maxWalkTime_ << endl;
    }
    else if (regex_match(line, match, destinationRegex)) {
        destination_ = graph_->findVertex(stoi(match[1]));
        cout << "Destination: " << destination_->getId() << endl;
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
                    avoidNodes_.push_back(graph_->findVertex(stoi(token)));
            }
        }
        cout << "AvoidNodes:";
        for (Vertex* n : avoidNodes_)
            cout << " " << n->getId();
        cout << endl;
    }
    else if (regex_match(line, match, avoidSegmentsRegex)) {
        string segStr = match[1];
        // Usar outra regex para extrair cada par dentro dos parênteses:
        regex segPairRegex(R"(\(\s*(\d+)\s*,\s*(\d+)\s*\))");
        auto segBegin = sregex_iterator(segStr.begin(), segStr.end(), segPairRegex);
        auto segEnd = sregex_iterator();
        for (auto it = segBegin; it != segEnd; ++it) {
            Vertex* temp_source =  graph_->findVertex(stoi((*it)[1]));
            Vertex* temp_target = graph_->findVertex(stoi((*it)[2]));
            Edge* existingEdge;
            for (Edge* edge : temp_source->getAdj()) {
                if (edge->getDest() == temp_target) { // Se o destino da aresta for o temp_target
                   existingEdge = edge;
                   break;
                }
            }
            avoidSegments_.push_back(existingEdge);

        }
        cout << "AvoidSegments:";
        cout << " (";
        for (Edge* seg : avoidSegments_) {
            cout << seg->getOrig()->getId() << "," << seg->getDest()->getId() << " , ";
        }
        cout << ")";
        cout << endl;
    }
    else if (regex_match(line, match, includeNodeRegex)) {
        string inc = match[1];
        if (!inc.empty())
            includeNode_ = graph_->findVertex(stoi(inc));
        cout << "IncludeNode: " << includeNode_->getId() << endl;
    }
    else {
        cout << "Linha não reconhecida: " << line << endl;
    }
}

void Write(ofstream& file, string label,int number){
    file << label << ":" << number << endl;
}

void WriteWithoutExtra(ofstream& file, string label, vector<int> numbers) {
    file << label << ":";
    for (int i = 0; i < numbers.size(); i++) {
        file << numbers[i];
        if ( i < numbers.size() - 1) {
            file << ",";
        }
    }
}

void WriteWithExtra(ofstream& file, string label, vector<int> numbers, int extra) {
    file << label << ":";
    for (int i = 0; i < numbers.size(); i++) {
        file << numbers[i];
        if ( i < numbers.size() - 1) {
            file << ",";
        }
    }
    file << "("<< extra << ")" << endl;
}