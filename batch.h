#ifndef BATCH_H
#define BATCH_H

#include "graph.h"
#include <string>
#include <vector>
#include <regex>

class Batch {
public:
    void setGraph(Graph* graph);

    bool loadFromFile(const std::string& filename);

    std::string getMode() const;
    Vertex* getSource() const;
    Vertex* getDestination() const;
    double getMaxWalkTime() const;
    const std::vector<Vertex*>& getAvoidNodes() const;
    const std::vector<Edge*>& getAvoidSegments() const;
    Vertex* getIncludeNode() const;

private:
    Graph* graph_;

    std::string mode_;
    Vertex* source_;
    Vertex* destination_;
    double maxWalkTime_;
    std::vector<Vertex*> avoidNodes_;
    std::vector<Edge*> avoidSegments_;
    Vertex* includeNode_;

    void processLine(const std::string& line);
    void processAvoidNodes(const std::string& nodesStr);
    void processAvoidSegments(const std::string& segStr);
};

#endif // BATCH_H