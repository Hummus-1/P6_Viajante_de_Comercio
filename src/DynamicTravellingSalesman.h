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

class DTS : public TravellingSalesman {
  protected:
    std::vector<std::string> solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode, unsigned destinyNode);
};

}