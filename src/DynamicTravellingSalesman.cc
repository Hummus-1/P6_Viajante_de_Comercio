#include "DynamicTravellingSalesman.h"

namespace TSP {

std::vector<std::string> DTS::solveProblem(AdjacencyMatrix& adjacencyMatrix, unsigned originNode) {
  std::vector<bool>(adjacencyMatrix.numberOfNodes(), false);
  std::map<std::vector<unsigned>, std::pair<int, unsigned> > costsMap;
  std::vector<std::string> path;
  for(unsigned i = 0; i < adjacencyMatrix.numberOfNodes(); ++i) {
    if(i != originNode)
      costsMap[std::vector<unsigned>{originNode, i}] = std::make_pair(adjacencyMatrix.at(originNode, i), 1 << i);
  }
  for(unsigned i = 0; i < adjacencyMatrix.numberOfNodes() - 1 && !stop; ++i) {
    costsMap = dynamicSolve(adjacencyMatrix, originNode, costsMap);
  }
  for(unsigned i = 0; i < costsMap.begin()->first.size(); ++i) {
    path.push_back(adjacencyMatrix.convertNode(costsMap.begin()->first[i]));
  }
  return path;
}

std::map<std::vector<unsigned>, std::pair<int, unsigned> > DTS::dynamicSolve(AdjacencyMatrix& adjacencyMatrix, unsigned originNode, std::map<std::vector<unsigned>, std::pair<int, unsigned> > costsMap) {
  std::map<std::vector<unsigned>, std::pair<int, unsigned> > newCostsMap;
  for(unsigned i = 0; i < adjacencyMatrix.numberOfNodes(); ++i) {
    std::map<unsigned, path_cost> subsetMap;
    for(auto& node : costsMap) {
      if(std::find(node.first.begin(), node.first.end(), i) == node.first.end()) {
        path_cost newPath = std::make_pair(node.first, node.second.first + adjacencyMatrix.at(node.first[node.first.size() - 1], i));
        newPath.first.push_back(i);
        if((subsetMap.find(node.second.second + (1 << (i))) == subsetMap.end()) ||(newPath.second < subsetMap.find(node.second.second + (1 << (i)))->second.second))
            subsetMap[node.second.second + (1 << (i))] = newPath;
      }
      else if(node.first.size() == adjacencyMatrix.numberOfNodes() && i == originNode) {
        path_cost newPath = std::make_pair(node.first, node.second.first += adjacencyMatrix.at(node.first[node.first.size() - 1], i));
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

// N -> Nums Size K -> sequence size
std::vector<std::vector<unsigned> > comb(int N, int K)
{
    std::vector<std::vector<unsigned> > combinations;
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's
    unsigned k = 0;
    do {
        combinations.push_back(std::vector<unsigned>(0));
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) combinations[k].push_back(i);
        }
        std::cout << std::endl;
        ++k;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    return combinations;
}

}