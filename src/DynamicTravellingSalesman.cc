#include "DynamicTravellingSalesman.h"

namespace TSP {

std::vector<std::string> DTS::solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode) {
  std::vector<bool>(adjacencyMatrix.numberOfNodes(), false);
  pathMap costsMap;
  std::vector<std::string> path;
  for(unsigned i = 0; i < adjacencyMatrix.numberOfNodes(); ++i) {
    if(i != originNode)
      costsMap[std::vector<unsigned>{originNode, i}] = std::make_pair(adjacencyMatrix.at(originNode, i), 1 << i);
  }
  for(unsigned i = 0; i < adjacencyMatrix.numberOfNodes() - 1; ++i) {
    costsMap = dynamicSolve(adjacencyMatrix, originNode, costsMap);
  }
  for(unsigned i = 0; i < costsMap.begin()->first.size(); ++i) {
    path.push_back(adjacencyMatrix.convertNode(costsMap.begin()->first[i]));
  }
  return path;
}

pathMap DTS::dynamicSolve(AdjacencyMatrix& adjacencyMatrix, unsigned originNode, pathMap costsMap) {
  pathMap newCostsMap;
  for(unsigned i = 0; i < adjacencyMatrix.numberOfNodes(); ++i) {
    std::map<unsigned, std::pair<std::vector<unsigned>, long unsigned> > subsetMap;
    for(auto& node : costsMap) {
      if(std::find(node.first.begin(), node.first.end(), i) == node.first.end()) {
        std::pair<std::vector<unsigned>, long unsigned> newPath = std::make_pair(node.first, node.second.first + adjacencyMatrix.at(node.first[node.first.size() - 1], i));
        newPath.first.push_back(i);
        if((subsetMap.find(node.second.second + (1 << (i))) == subsetMap.end()) ||(newPath.second < subsetMap.find(node.second.second + (1 << (i)))->second.second))
            subsetMap[node.second.second + (1 << (i))] = newPath;
      }
      else if(node.first.size() == adjacencyMatrix.numberOfNodes() && i == originNode) {
        std::pair<std::vector<unsigned>, long unsigned> newPath = std::make_pair(node.first, node.second.first += adjacencyMatrix.at(node.first[node.first.size() - 1], i));
        newPath.first.push_back(i);
        if((subsetMap.find(node.second.second + (1 << (i))) == subsetMap.end()) ||(newPath.second < subsetMap.find(node.second.second + (1 << (i)))->second.second))
            subsetMap[node.second.second + (1 << (i))] = newPath;
      }
    }
    for(auto& node : subsetMap) {
      std::pair<int, unsigned> a(node.second.second, node.first);
      newCostsMap.insert(std::make_pair(node.second.first, std::make_pair(node.second.second, node.first)));
    }
  }
  return newCostsMap;
}

}