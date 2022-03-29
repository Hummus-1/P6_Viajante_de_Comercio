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
    AdjacencyMatrix(int numberOfNodes);
    AdjacencyMatrix(std::string path);

    void exportInstance(std::string path);

    void addNode(std::string nodeName);
    void addConexion(std::string originNode, std::string destinyNode);
    int at(std::string originNode, std::string destinyNode) const;
    std::string closerConexion(std::string originNode);
    int numberOfNodes();
  private:
    int& at(std::string originNode, std::string destinyNode);
    void importInstance(std::string path);
    Matrix adjacencyMatrix_;
    std::vector<std::string> nodes_;
    std::map<std::string, unsigned> nodesRelation_;
};

}