#include "GreedyTravellingSalesman.h"

namespace TSP {

std::vector<std::string> GTS::solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode, unsigned destinyNode) {
  std::vector<bool> visitedNodes(adjacencyMatrix.numberOfNodes(), false);
  std::vector<std::string> path;
  unsigned actualNode = originNode;
  path.push_back(adjacencyMatrix.convertNode(actualNode));
  visitedNodes[actualNode] = true;
  while(actualNode != destinyNode) {
    actualNode = adjacencyMatrix.closerConnection(actualNode, visitedNodes);
    path.push_back(adjacencyMatrix.convertNode(actualNode));
    visitedNodes[actualNode] = true;
  }
  return path;
}

}