#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <thread>
#include <chrono> 
#include <map>
#include <filesystem>
#include <math.h>

#include "GreedyTravellingSalesman.h"
#include "RudeTravellingSalesman.h"
#include "DynamicTravellingSalesman.h"
#include "menuUtility.h"

unsigned int factorial(unsigned int n) 
{
    if (n == 0)
       return 1;
    return n * factorial(n - 1);
}

void printColumn(std::string value, unsigned length, std::string final) {
  std::cout << *(new std::string((length - value.size()) / 2, ' ')) <<
  " " << value <<
  *(new std::string((length - value.size()) / 2 + (length - value.size()) % 2, ' ')) << final; 
}

unsigned maxSizeForTime(unsigned time, char algorithm, std::map<std::string, double> &timeMap) {
  float actualTime = 0;
  unsigned size = 2;
  for(; actualTime <= time; ++size) {
    if(algorithm == 'g') {
      actualTime = timeMap["greedy"] * size * 750;
    } else if(algorithm == 'r') {
      actualTime = (factorial(size) * timeMap["rude"]) / 750;
    } else if(algorithm == 'd') {
      actualTime = (std::pow(2, size) * std::pow(size, 2) * timeMap["dynamic"]) / 750;
    }
  }
  return size - 2;
}

std::map<std::string, double> howMuchTime(bool callback = false) {
  if(callback)
    howMuchTime();
  std::map<std::string, double> timeMap;
  TSP::AdjacencyMatrix adjMatrix(7);
  TSP::GTS greedyTSP;
  TSP::RTS rudeTSP;
  TSP::DTS dynamicTSP;

  clock_t t_start = clock();
  greedyTSP.Solve(adjMatrix, adjMatrix.convertNode(2));
  timeMap["greedy"] = ((double)(clock() - t_start)/CLOCKS_PER_SEC) / 7;

  t_start = clock();
  rudeTSP.Solve(adjMatrix, adjMatrix.convertNode(2));
  timeMap["rude"] = ((double)(clock() - t_start)/CLOCKS_PER_SEC) / 7;

  t_start = clock();
  dynamicTSP.Solve(adjMatrix, adjMatrix.convertNode(2));
  timeMap["dynamic"] = ((double)(clock() - t_start)/CLOCKS_PER_SEC) / 7;

  return timeMap;
}

void printTSP(unsigned size, unsigned maxSeconds, TSP::AdjacencyMatrix &adjMatrix, std::map<std::string, unsigned> sizeMap, unsigned iterations = 1) {
  std::map<std::string, std::pair<float, unsigned> > timeMap;
  timeMap["rude"] = std::make_pair(0, 0);
  timeMap["greedy"] = std::make_pair(0, 0);
  timeMap["dynamic"] = std::make_pair(0, 0);

  printColumn(std::to_string(size), 6, " |-> ");
  for(unsigned i = 0; i < iterations; ++i) {
    TSP::RTS rudeTSP;
    if(sizeMap["rude"] < size) {
      TSP::AdjacencyMatrix newAdjMatrix = adjMatrix.reduce(sizeMap["rude"]);
      timeMap["rude"].first += 600;
      timeMap["rude"].second += newAdjMatrix.pathWeight(rudeTSP.Solve(newAdjMatrix, newAdjMatrix.convertNode(1)));
    }
    else {
      clock_t t_start_r = clock();
      timeMap["rude"].second += adjMatrix.pathWeight(rudeTSP.Solve(adjMatrix, adjMatrix.convertNode(1)));
      timeMap["rude"].first += (double)(clock() - t_start_r)/CLOCKS_PER_SEC;
    }

    TSP::GTS greedyTSP;
    if(sizeMap["greedy"] < size) {
      TSP::AdjacencyMatrix newAdjMatrix = adjMatrix.reduce(sizeMap["greedy"]);
      timeMap["greedy"].first += 600;
      timeMap["greedy"].second += newAdjMatrix.pathWeight(greedyTSP.Solve(newAdjMatrix, newAdjMatrix.convertNode(1)));
    }
    else {
      clock_t t_start_r = clock();
      timeMap["greedy"].second += adjMatrix.pathWeight(greedyTSP.Solve(adjMatrix, adjMatrix.convertNode(1)));
      timeMap["greedy"].first += (double)(clock() - t_start_r)/CLOCKS_PER_SEC;
    }

    TSP::DTS dynamicTSP;
    if(sizeMap["dynamic"] < size) {
      TSP::AdjacencyMatrix newAdjMatrix = adjMatrix.reduce(sizeMap["dynamic"]);
      timeMap["dynamic"].first += 600;
      timeMap["dynamic"].second += newAdjMatrix.pathWeight(dynamicTSP.Solve(newAdjMatrix, newAdjMatrix.convertNode(1)));
    }
    else {
      clock_t t_start_r = clock();
      timeMap["dynamic"].second += adjMatrix.pathWeight(dynamicTSP.Solve(adjMatrix, adjMatrix.convertNode(1)));
      timeMap["dynamic"].first += (double)(clock() - t_start_r)/CLOCKS_PER_SEC;
    }
    adjMatrix = TSP::AdjacencyMatrix(adjMatrix.numberOfNodes());
  }
  printColumn(std::to_string(timeMap["rude"].second / iterations), 12, " | ");
  printColumn(std::to_string(timeMap["rude"].first / iterations), 12, " | ");
  printColumn(std::to_string(timeMap["greedy"].second / iterations), 12, " | ");
  printColumn(std::to_string(timeMap["greedy"].first / iterations), 12, " | ");
  printColumn(std::to_string(timeMap["dynamic"].second / iterations), 12, " | ");
  printColumn(std::to_string(timeMap["dynamic"].first / iterations), 12, " | \n");
}

int main(int argc, char **argv) {
  try {
    if(argc == 2) {
      TSP::AdjacencyMatrix adjMatrix(std::stoi(argv[1]));
      adjMatrix.exportInstance("adjMatrix.txt");
      return 0;
    }
    if(argc < 3 || argc > 4)
        throw std::length_error("2 arguments required\nExecution: ./TSP filename maxSeconds\n");
    float maxSeconds = std::stoi(argv[2]);
    unsigned numberOfIterations = (argc == 4) ? std::stoi(argv[3]) : 1;
    std::map<std::string, double> timeMap = howMuchTime(true);
    std::map<std::string, unsigned> sizeMap;
    sizeMap["rude"] = maxSizeForTime(maxSeconds, 'r', timeMap);
    sizeMap["greedy"] = maxSizeForTime(maxSeconds, 'g', timeMap);
    sizeMap["dynamic"] = maxSizeForTime(maxSeconds, 'd', timeMap);
    sizeMap["rude"] = maxSizeForTime(maxSeconds, 'r', timeMap);
    sizeMap["greedy"] = maxSizeForTime(maxSeconds, 'g', timeMap);
    sizeMap["dynamic"] = maxSizeForTime(maxSeconds, 'd', timeMap);
    try {
      unsigned maxSize = std::stoi(argv[1]);
      std::cout << "  Size           Brute Force Cost/Time           Greedy Cost/Time                Dynamic Cost/Time\n";
      for(unsigned i = 2; i <= maxSize; ++i) {
        TSP::AdjacencyMatrix adjMatrix(i);
        printTSP(i, maxSeconds, adjMatrix, sizeMap, numberOfIterations);
      }
    }
    catch(std::length_error &e) {
      std::cout << e.what() << "\n";
    }
    catch(std::invalid_argument &e) {
      std::string path = argv[1];
      std::cout << "  Size          Brute Force Cost/Time            Greedy Cost/Time                Dynamic Cost/Time\n";
      for (const auto & entry : std::filesystem::directory_iterator(path)) {
        TSP::AdjacencyMatrix adjMatrix(entry.path());
        printTSP(adjMatrix.numberOfNodes(), maxSeconds, adjMatrix, sizeMap);
      }
    }
  }
  catch(std::invalid_argument &e) {
    std::cout << "The second argument should be a number\nExecution: ./TSP filename maxSeconds\n";
  }
}