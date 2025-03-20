#ifndef BATCH_H
#define BATCH_H

#include "graph.h"
#include <string>
#include <vector>
#include <regex>

struct Caminho {
    vector<int> route;
    int time;
    int park;
    vector<int> wroute;
    int wtime;
    int totaltime;
};

class Batch {
public:
    Batch(Graph* graph)
        : graph_(graph),
          mode_(""),                    // guardem a minha palavra, Maranhão um dia vai ganhar Uma libertadores e o melhor clube do mundo
          source_(nullptr),
          destination_(nullptr),
          maxWalkTime_(0.0),
          avoidNodes_({}),
          avoidSegments_({}),
          includeNode_(nullptr),
          file_(nullptr)
    {};
    bool loadFromFile(const std::string& filename);

    void generateOutput() const {
        ostringstream oss;
        oss << "Source:" << (to_string(source_->getId())) << endl;
        oss << "Destination:" << (to_string(destination_->getId())) << endl;

        bool hasRestrictions = includeNode_ != nullptr || !avoidNodes_.empty() || !avoidSegments_.empty();

        if (hasRestrictions) {
            Caminho restrictedRoute;/*  <Lugar Digno do Dijkstra de Nodes e camingos restritos>  */
            oss << "Restricted" << mode_ << "Route:" << restrictedRoute.route << "(" << restrictedRoute.time << ")" << endl;
        } else if (mode_ == "driving" || mode_ == "walking") {
            Caminho bestRoute;  /*  <Dijkstra simples>  */
            Caminho alternateRoute;  /*  <epa... n é simples mas n é dificil>  */
            oss << "BestDrivingRoute:" << bestRoute.route <<"(" << bestRoute.time << ")" << endl;
            oss << "AlternativeDrivingRoute:" << alternateRoute << "\n";
        } else if (mode_ == "driving-walking") {

            std::vector<Caminho> routes; /* Destinado a Dijkstra bue dificeis*/
            /*
             * Lugar em construção
             *
             */
            for (size_t i = 0; i < routes.size(); ++i) {
                oss << "DrivingRoute" << (i + 1) << ":" << routes[i].route<< "(" << routes[i].time << ")"  << endl;
                oss << "ParkingNode" << (i + 1) << routes[i].park << endl;
                oss << "WalkingRoute" << (i + 1) <<routes[i].wroute << "(" << routes[i].wtime << ")"<< endl;
                oss << "TotalTime" << (i + 1) << routes[i].totaltime <<endl;
            }

            // Verificar se o MaxWalkTime foi excedido
            if (routes.size() > 1) {
                oss << "Message:No possible route with max. walking time of "
                    << maxWalkTime_ << endl;
            }
        }
        *file_<< (oss.str());
    }

    std::string getMode() ;
    Vertex* getSource() ;
    Vertex* getDestination() ;
    double getMaxWalkTime();
    const std::vector<Vertex*>& getAvoidNodes() ;
    const std::vector<Edge*>& getAvoidSegments() ;
    Vertex* getIncludeNode() ;
    std::ofstream* getFile_();
    void setOutputFile(string strinG);


private:
    Graph* graph_;

    string mode_;
    Vertex* source_;
    Vertex* destination_;
    double maxWalkTime_;
    vector<Vertex*> avoidNodes_;
    vector<Edge*> avoidSegments_;
    Vertex* includeNode_;
    ofstream* file_;

    void processLine(const string& line);
};

#endif // BATCH_H