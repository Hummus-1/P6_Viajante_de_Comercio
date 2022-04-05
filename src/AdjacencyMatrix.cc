#include "AdjacencyMatrix.h"

namespace TSP {

AdjacencyMatrix::AdjacencyMatrix(unsigned numberOfNodes) : 
                 adjacencyMatrix_(*new Matrix(numberOfNodes, numberOfNodes)) {
  unsigned stringLength = 1 + numberOfNodes / 20;
  for(unsigned i = 0; i < numberOfNodes; ++i) {
    std::string nodeName = generateRandomString(stringLength);
    if(nodesRelation_.find(nodeName) != nodesRelation_.end())
      --i;
    else {
      nodesRelation_.insert(std::make_pair(nodeName, i));
      nodes_.push_back(nodeName);
    }
  }
}

AdjacencyMatrix::AdjacencyMatrix(std::string path) {
  importInstance(path);
}

void AdjacencyMatrix::importInstance(std::string path) {
  unsigned lineCount = 1;
  try {
    std::queue<std::string> fileData = ReadFile(path, 'v');
    unsigned numberOfNodes = std::stoi(fileData.front());
    fileData.pop();
    adjacencyMatrix_ = *new Matrix(numberOfNodes, numberOfNodes);
    ++lineCount;
    while(!fileData.empty()) {
      std::string originNode = fileData.front();
      fileData.pop();
      if(nodesRelation_.find(originNode) == nodesRelation_.end()) {
        nodesRelation_.insert(std::make_pair(originNode, nodes_.size()));
        nodes_.push_back(originNode);
      }
      std::string destinyNode = fileData.front();
      fileData.pop();
      if(nodesRelation_.find(destinyNode) == nodesRelation_.end()) {
        nodesRelation_.insert(std::make_pair(destinyNode, nodes_.size()));
        nodes_.push_back(destinyNode);
      }
      int weight = std::stoi(fileData.front());
      this->at(originNode, destinyNode) = weight;
      this->at(destinyNode, originNode) = weight;
      fileData.pop();
      ++lineCount;
    }
  }
  catch(std::ifstream::failure &error) {
    throw std::runtime_error(error.what());
  }
  catch(std::invalid_argument &error) {
    throw std::runtime_error(error.what());
  } 
}

void AdjacencyMatrix::exportInstance(std::string path) {
  std::fstream outputFile = OpenFile(path, 'w');
  unsigned numberOfNodes = nodes_.size();
  outputFile << numberOfNodes << '\n';
  for(unsigned i = 0; i < numberOfNodes; ++i) {
    for(unsigned j = i + 1; j < numberOfNodes; ++j) {
      outputFile << nodes_[i] << ' ' << nodes_[j] << ' ' << adjacencyMatrix_[i][j] << '\n';
    }
  }
}

int AdjacencyMatrix::at(std::string originNode, std::string destinyNode) const {
  return adjacencyMatrix_[nodesRelation_.at(originNode)][nodesRelation_.at(destinyNode)];
}

int AdjacencyMatrix::at(unsigned originNode, unsigned destinyNode) const {
  return adjacencyMatrix_[originNode][destinyNode];
}

int AdjacencyMatrix::pathWeight(std::vector<std::string> path) {
  int weight = 0;
  for(unsigned i = 1; i < path.size(); ++i) {
    weight += at(path[i - 1], path[i]);
  }
  return weight;
}

int AdjacencyMatrix::pathWeight(std::vector<unsigned> path) {
  int weight = 0;
  for(unsigned i = 1; i < path.size(); ++i) {
    weight += at(path[i - 1], path[i]);
  }
  return weight;
}

int& AdjacencyMatrix::at(std::string originNode, std::string destinyNode) {
  return adjacencyMatrix_[nodesRelation_[originNode]][nodesRelation_[destinyNode]];
}

unsigned AdjacencyMatrix::closerConnection(unsigned originNode, std::vector<bool> visitedNodes) {
  if(visitedNodes.size() == 0)
    visitedNodes = *new std::vector<bool>(numberOfNodes(), false);
  int minConnection = -1;
  for(unsigned i = 0; i < nodes_.size(); ++i) {
    if(i != originNode && !visitedNodes[i]) {
      if(minConnection < 0 || adjacencyMatrix_[originNode][i] < adjacencyMatrix_[originNode][minConnection]) {
        minConnection = i;
      }
    }
  }
  return minConnection;
}

unsigned AdjacencyMatrix::numberOfNodes() {
  return nodes_.size();
}

AdjacencyMatrix AdjacencyMatrix::reduce(unsigned numerOfNodes) {
  AdjacencyMatrix reducedMatrix = *this;
  reducedMatrix.adjacencyMatrix_.resize(numerOfNodes, numerOfNodes);
  reducedMatrix.nodes_.resize(numerOfNodes);
  return reducedMatrix;
}

}