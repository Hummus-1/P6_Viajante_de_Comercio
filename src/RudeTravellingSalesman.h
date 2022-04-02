#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

#include "AdjacencyMatrix.h"
#include "TravellingSalesman.h"
#include "menuUtility.h"

namespace TSP {

class RTS : public TravellingSalesman {
  protected:
    std::vector<std::string> solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode);
    std::vector<std::vector<unsigned> > allCombinations(AdjacencyMatrix& adjacencyMatrix, std::vector<unsigned> myPath);
};

}