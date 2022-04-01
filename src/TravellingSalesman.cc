#include "TravellingSalesman.h"

namespace TSP {

std::vector<std::string> TravellingSalesman::Solve(int numberOfNodes, std::string originNode, std::string destinyNode) {
  AdjacencyMatrix adjacencyMatrix(numberOfNodes);
  return solveProblem(adjacencyMatrix, adjacencyMatrix.convertNode(originNode), adjacencyMatrix.convertNode(destinyNode));
}

std::vector<std::string> TravellingSalesman::Solve(std::string path, std::string originNode, std::string destinyNode) {
  AdjacencyMatrix adjacencyMatrix(path);
  return solveProblem(adjacencyMatrix, adjacencyMatrix.convertNode(originNode), adjacencyMatrix.convertNode(destinyNode));
}

std::vector<std::string> TravellingSalesman::Solve(AdjacencyMatrix adjacencyMatrix, std::string originNode, std::string destinyNode) {
  return solveProblem(adjacencyMatrix, adjacencyMatrix.convertNode(originNode), adjacencyMatrix.convertNode(destinyNode));
}

}