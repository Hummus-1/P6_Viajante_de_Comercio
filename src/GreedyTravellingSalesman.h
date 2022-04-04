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

/**
 * @brief Solves the TSP with a greedy algorithm
 * 
 */
class GTS : public TravellingSalesman {
  protected:
    /**
     * @brief Solve the problem with the adjacency matrix given and starting with the originNode
     * 
     * @param adjacencyMatrix The adjacency matrix to compute
     * @param originNode The origin node to apply the algorithm
     * @return std::vector<std::string> The solution path
     */
    std::vector<std::string> solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode);
};

}