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

/**
 * @brief Solve the TSP with an brute force algorithm
 * 
 */
class RTS : public TravellingSalesman {
  protected:
    /**
     * @brief Solve the problem with the adjacency matrix given and starting with the originNode
     * 
     * @param adjacencyMatrix The adjacency matrix to compute
     * @param originNode The origin node to start the algorithm
     * @return std::vector<std::string> The solution path
     */
    std::vector<std::string> solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode);

    /**
     * @brief Recursive function that return all the possible combination for the TSP
     * 
     * @param adjacencyMatrix The adjacency matrix to compute
     * @param myPath The actual path
     * @return std::vector<std::vector<unsigned> > A vector of possible paths
     */
    std::vector<std::vector<unsigned> > allCombinations(AdjacencyMatrix& adjacencyMatrix, std::vector<unsigned> myPath);
};

}