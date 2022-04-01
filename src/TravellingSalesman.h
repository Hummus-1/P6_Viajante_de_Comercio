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
    TravellingSalesman() {}
    ~TravellingSalesman() {}
    std::vector<std::string> Solve(int numberOfNodes, std::string originNode, std::string destinyNode);
    std::vector<std::string> Solve(std::string path, std::string originNode, std::string destinyNode);
    std::vector<std::string> Solve(AdjacencyMatrix adjacencyMatrix, std::string originNode, std::string destinyNode);
  protected:
    virtual std::vector<std::string> solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode, unsigned destinyNode) = 0;
};

}