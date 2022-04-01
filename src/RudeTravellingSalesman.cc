#include "RudeTravellingSalesman.h"

namespace TSP {

std::vector<std::string> RTS::solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode, unsigned destinyNode) {
  if(originNode == destinyNode) {
    return *new std::vector<std::string>{adjacencyMatrix.convertNode(originNode)};
  }
  std::vector<std::vector<unsigned> > paths = allCombinations(adjacencyMatrix, destinyNode, *new std::vector<unsigned>{originNode});
  std::vector<unsigned> cx{adjacencyMatrix.convertNode("c"), adjacencyMatrix.convertNode("x")};
  int minWeight = INT32_MAX;
  std::vector<unsigned> minPath;
  for(unsigned i = 0; i < paths.size(); ++i) {
    int actualWeight = adjacencyMatrix.pathWeight(paths[i]);
    if(actualWeight < minWeight) {
      minPath = paths[i];
      minWeight = actualWeight;
    }
  }
  std::vector<std::string> minPathNames;
  for(unsigned i = 0; i < minPath.size(); ++i) {
    minPathNames.push_back(adjacencyMatrix.convertNode(minPath[i]));
  }
  return minPathNames;
}

std::vector<std::vector<unsigned> > RTS::allCombinations(AdjacencyMatrix& adjacencyMatrix, unsigned destinyNode, std::vector<unsigned> myPath) {
  std::vector<std::vector<unsigned> > paths;
  for(unsigned i = 0; i < adjacencyMatrix.numberOfNodes(); ++i) {
    std::vector<unsigned> newPath = myPath;
    newPath.push_back(i);
    if(i == destinyNode) {
      paths.push_back(newPath);
    }
    else if(std::lower_bound(myPath.begin(), myPath.end(), i) == myPath.end()) {
      std::vector<std::vector<unsigned> > newPaths = allCombinations(adjacencyMatrix, destinyNode, newPath);
      paths.reserve(paths.size() + newPaths.size());
      paths.insert(paths.end(), newPaths.begin(), newPaths.end());
    }
  }
  return paths;
}

}