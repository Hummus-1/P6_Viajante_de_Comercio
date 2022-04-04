#include "RudeTravellingSalesman.h"

namespace TSP {

std::vector<std::string> RTS::solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode) {
  std::vector<std::vector<unsigned> > paths = allCombinations(adjacencyMatrix, *new std::vector<unsigned>{originNode});
  int minWeight = INT32_MAX;
  std::vector<unsigned> minPath;
  std::vector<std::string> minPathNames;
  for(unsigned i = 0; i < paths.size(); ++i) {
    int actualWeight = adjacencyMatrix.pathWeight(paths[i]);
    if(actualWeight < minWeight) {
      minPath = paths[i];
      minWeight = actualWeight;
    }
  }
  for(unsigned i = 0; i < minPath.size(); ++i) {
    minPathNames.push_back(adjacencyMatrix.convertNode(minPath[i]));
  }
  return minPathNames;
}

std::vector<std::vector<unsigned> > RTS::allCombinations(AdjacencyMatrix& adjacencyMatrix, std::vector<unsigned> myPath) {
  std::vector<std::vector<unsigned> > paths;
  for(unsigned i = 0; i < adjacencyMatrix.numberOfNodes(); ++i) {
    std::vector<unsigned> newPath = myPath;
    newPath.push_back(i);
    if(adjacencyMatrix.numberOfNodes() == (newPath.size() - 1) && i == myPath[0]) {
      paths.push_back(newPath);
      return paths;
    }
    else if(std::find(myPath.begin(), myPath.end(), i) == myPath.end()) {
      std::vector<std::vector<unsigned> > newPaths = allCombinations(adjacencyMatrix, newPath);
      paths.reserve(paths.size() + newPaths.size());
      paths.insert(paths.end(), newPaths.begin(), newPaths.end());
    }
  }
  return paths;
}

}