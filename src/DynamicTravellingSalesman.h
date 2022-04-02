#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

#include "AdjacencyMatrix.h"
#include "TravellingSalesman.h"
#include "menuUtility.h"

typedef std::pair<std::vector<unsigned>, int> path_cost;

namespace TSP {

class DTS : public TravellingSalesman {
  protected:
    std::vector<std::string> solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode);
    std::map<std::vector<unsigned>, std::pair<int, unsigned> > dynamicSolve(AdjacencyMatrix& adjacencyMatrix, unsigned originNode, std::map<std::vector<unsigned>, std::pair<int, unsigned> > costsMap);
};

}