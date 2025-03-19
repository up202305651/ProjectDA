#ifndef BATCH_H
#define BATCH_H

#include "graph.h"
#include <vector>

bool batch(Graph* graph, 
           std::string* Mode, 
           Vertex*& Source,          // Referência a ponteiro
           Vertex*& Destination,     // Referência a ponteiro
           double* MaxWalkTime, 
           std::vector<Vertex*>& AvoidNodes, // Vetor por referência
           std::vector<Edge*>& AvoidSegments, // Vetor por referência
           Vertex*& IncludeNode);     // Referência a ponteiro

#endif //BATCH_H