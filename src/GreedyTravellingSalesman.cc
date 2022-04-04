#include "GreedyTravellingSalesman.h"

namespace TSP {

std::vector<std::string> GTS::solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode) {
  std::vector<bool> visitedNodes(adjacencyMatrix.numberOfNodes(), false);
  std::vector<std::string> path;
  unsigned actualNode = originNode;
  path.push_back(adjacencyMatrix.convertNode(actualNode));
  visitedNodes[actualNode] = true;
  unsigned numberOfVisitedNodes = 1;
  while(numberOfVisitedNodes != adjacencyMatrix.numberOfNodes()) {
    actualNode = adjacencyMatrix.closerConnection(actualNode, visitedNodes);
    path.push_back(adjacencyMatrix.convertNode(actualNode));
    visitedNodes[actualNode] = true;
    ++numberOfVisitedNodes;
  }
  path.push_back(adjacencyMatrix.convertNode(originNode));
  return path;
}

}