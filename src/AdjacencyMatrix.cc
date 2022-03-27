#include "AdjacencyMatrix.h"

namespace TSP {

AdjacencyMatrix::AdjacencyMatrix(int numberOfNodes) : 
                 adjacencyMatrix_(*new Matrix(numberOfNodes, numberOfNodes)) {
  int stringLength = 1 + numberOfNodes / 20;
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
  int numberOfNodes = nodes_.size();
  outputFile << numberOfNodes << '\n';
  int numberOfLines = ((numberOfNodes * (numberOfNodes - 1)) / 2);
  for(unsigned i = 0; i < numberOfNodes; ++i) {
    for(unsigned j = i + 1; j < numberOfNodes; ++j) {
      outputFile << nodes_[i] << ' ' << nodes_[j] << ' ' << adjacencyMatrix_[i][j] << '\n';
    }
  }
}

void AdjacencyMatrix::addNode(std::string nodeName) {

}

void AdjacencyMatrix::addConexion(std::string originNode, std::string destinyNode) {

}

int AdjacencyMatrix::at(std::string originNode, std::string destinyNode) const {
  adjacencyMatrix_[nodesRelation_.at(originNode)][nodesRelation_.at(destinyNode)];
}

int& AdjacencyMatrix::at(std::string originNode, std::string destinyNode) {
  return adjacencyMatrix_[nodesRelation_[originNode]][nodesRelation_[destinyNode]];
}

}