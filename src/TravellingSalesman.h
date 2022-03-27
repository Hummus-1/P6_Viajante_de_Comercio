#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "AdjacencyMatrix.h"
#include "menuUtility.h"

namespace TSP {

class TravellingSalesman {
  public:
    TravellingSalesman();
    ~TravellingSalesman();
    void Solve(int numberOfNodes, std::string originNode, std::string destinyNode);
    void Solve(std::string path, std::string originNode, std::string destinyNode);
    void Solve(AdjacencyMatrix adjacencyMatrix, std::string originNode, std::string destinyNode);
  protected:
    void solveProblem(AdjacencyMatrix adjacencyMatrix, std::string originNode, std::string destinyNode);
};

}