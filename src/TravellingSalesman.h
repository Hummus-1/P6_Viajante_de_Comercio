#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "AdjacencyMatrix.h"
#include "menuUtility.h"

namespace TSP {

/**
 * @brief The abstract class that define a base for implement an algorithm for the 
 *        Travelling Salesman Problem
 * @abstract
 */
class TravellingSalesman {
  public:
    TravellingSalesman() {}
    ~TravellingSalesman() {}

    /**
     * @brief Solve the Travelling Salesman Problem with the given number of nodes
     * 
     * @param numberOfNodes The number of nodes
     * @param originNode The origin node name
     * @return std::vector<std::string> The solution path
     */
    std::vector<std::string> Solve(int numberOfNodes, std::string originNode);

    /**
     * @brief Solve the Travelling Salesman Problem with the adjacency matrix of the file given
     * 
     * @param path The filepath
     * @param originNode The origin node name
     * @return std::vector<std::string> The solution path
     */
    std::vector<std::string> Solve(std::string path, std::string originNode);

    /**
     * @brief Solve the Travelling Salesman Problem with the adjacency matrix given
     * 
     * @param adjacencyMatrix The adjacency matrix
     * @param originNode The origin node name
     * @return std::vector<std::string> The solution path
     */
    std::vector<std::string> Solve(AdjacencyMatrix adjacencyMatrix, std::string originNode);
  protected:

    /**
     * @brief Particular problem solving to be implemented in the specific class
     * 
     * @param adjacencyMatrix The adjacency matrix to compute
     * @param originNode The origin node to apply the algorithm
     * @return std::vector<std::string> The solution path
     */
    virtual std::vector<std::string> solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode) = 0;
};

}