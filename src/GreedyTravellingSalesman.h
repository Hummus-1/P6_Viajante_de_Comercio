#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "AdjacencyMatrix.h"
#include "TravellingSalesman.h"
#include "menuUtility.h"

namespace TSP {

class GTS : public TravellingSalesman {
  public:
    // GTS();
    // ~GTS();
  protected:
    std::vector<std::string> solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode, unsigned destinyNode);
};

}