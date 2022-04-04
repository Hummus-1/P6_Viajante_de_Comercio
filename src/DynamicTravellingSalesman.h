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

typedef std::map<std::vector<unsigned>, std::pair<int, long unsigned> > pathMap;

namespace TSP {

/**
 * @brief Solves the TSP with an dynamic programming algorithm
 * 
 */
class DTS : public TravellingSalesman {
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
     * @brief Increment by one node the current subset of paths
     * 
     * @param adjacencyMatrix The adjacency matrix to compute
     * @param originNode The origin node to start the algorithm
     * @param costsMap The previous computed map with the subpaths as keys and containing each one the
     *                 cost of the path and it's bitmasking identification
     * @return pathMap The new costs map
     */
    pathMap dynamicSolve(AdjacencyMatrix& adjacencyMatrix, unsigned originNode, pathMap costsMap);
};

}