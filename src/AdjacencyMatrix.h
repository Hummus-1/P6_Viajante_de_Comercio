#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
#include <ctime>

#include "Matrix.h"
//#include "RandomString.cc"
#include "menuUtility.h"

namespace TSP {

class AdjacencyMatrix {
  public: 
    AdjacencyMatrix(unsigned numberOfNodes);
    AdjacencyMatrix(std::string path);

    void exportInstance(std::string path);

    unsigned convertNode(std::string nodeName) {return nodesRelation_[nodeName];}
    std::string convertNode(unsigned nodeNumber) {return nodes_[nodeNumber];}
    int at(std::string originNode, std::string destinyNode) const;
    int at(unsigned originNode, unsigned destinyNode) const;
    unsigned numberOfNodes();
    int pathWeight(std::vector<std::string> path);
    int pathWeight(std::vector<unsigned> path);

    unsigned closerConnection(unsigned originNode, std::vector<bool> visitedNodes = *new std::vector<bool>(0));
  private:
    int& at(std::string originNode, std::string destinyNode);
    void importInstance(std::string path);


    Matrix adjacencyMatrix_;
    std::vector<std::string> nodes_;
    std::map<std::string, unsigned> nodesRelation_;
};

}