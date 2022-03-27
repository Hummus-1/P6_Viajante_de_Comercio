#include "TravellingSalesman.h"

namespace TSP {

void TravellingSalesman::Solve(int numberOfNodes, std::string originNode, std::string destinyNode) {
  AdjacencyMatrix adjacencyMatrix(numberOfNodes);
  solveProblem(adjacencyMatrix, originNode, destinyNode);
}

void TravellingSalesman::Solve(std::string path, std::string originNode, std::string destinyNode) {
  AdjacencyMatrix adjacencyMatrix(path);
  solveProblem(adjacencyMatrix, originNode, destinyNode);
}

void TravellingSalesman::Solve(AdjacencyMatrix adjacencyMatrix, std::string originNode, std::string destinyNode) {
  solveProblem(adjacencyMatrix, originNode, destinyNode);
}

}