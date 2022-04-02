#include "TravellingSalesman.h"

namespace TSP {

std::vector<std::string> TravellingSalesman::Solve(int numberOfNodes, std::string originNode) {
  AdjacencyMatrix adjacencyMatrix(numberOfNodes);
  return solveProblem(adjacencyMatrix, adjacencyMatrix.convertNode(originNode));
}

std::vector<std::string> TravellingSalesman::Solve(std::string path, std::string originNode) {
  AdjacencyMatrix adjacencyMatrix(path);
  return solveProblem(adjacencyMatrix, adjacencyMatrix.convertNode(originNode));
}

std::vector<std::string> TravellingSalesman::Solve(AdjacencyMatrix adjacencyMatrix, std::string originNode) {
  return solveProblem(adjacencyMatrix, adjacencyMatrix.convertNode(originNode));
}

}