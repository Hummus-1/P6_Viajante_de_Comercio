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

void printTSP(unsigned size, unsigned maxSeconds, TSP::AdjacencyMatrix &adjMatrix, std::map<std::string, double> timeMap) {
  printColumn(std::to_string(size), 6, " |-> ");

  double rudeTime = (factorial(size) * timeMap["rude"]) / 750;
  if((rudeTime > maxSeconds) || (rudeTime == 0.0)) {
    printColumn("EXCESSIVE", 12, " | ");
    printColumn("EXCESSIVE", 12, " | ");
  }
  else {
    TSP::RTS rudeTSP;
    clock_t t_start_r = clock();
    printColumn(std::to_string(adjMatrix.pathWeight(rudeTSP.Solve(adjMatrix, adjMatrix.convertNode(1)))), 12, " | ");
    printColumn(std::to_string((double)(clock() - t_start_r)/CLOCKS_PER_SEC), 12, " | ");
  }

  double greedyTime = timeMap["greedy"] * size * 750;
  if((greedyTime > maxSeconds) || greedyTime == 0.0) {
    printColumn("EXCESSIVE", 12, " | ");
    printColumn("EXCESSIVE", 12, " | ");
  }
  else {
    TSP::GTS greedyTSP;
    clock_t t_start_r = clock();
    printColumn(std::to_string(adjMatrix.pathWeight(greedyTSP.Solve(adjMatrix, adjMatrix.convertNode(1)))), 12, " | ");
    printColumn(std::to_string((double)(clock() - t_start_r)/CLOCKS_PER_SEC), 12, " | ");
  }

  double dynamicTime = (std::pow(2, size) * std::pow(size, 2) * timeMap["dynamic"]) / 750;
  if((dynamicTime > maxSeconds) || (dynamicTime == 0.0)) {
    printColumn("EXCESSIVE", 12, " | ");
    printColumn("EXCESSIVE", 12, " |\n");
  }
  else {
    TSP::DTS dynamicTSP;
    clock_t t_start_r = clock();
    printColumn(std::to_string(adjMatrix.pathWeight(dynamicTSP.Solve(adjMatrix, adjMatrix.convertNode(1)))), 12, " | ");
    printColumn(std::to_string((double)(clock() - t_start_r)/CLOCKS_PER_SEC), 12, " |\n");
  }
}

int main(int argc, char **argv) {
  try {
    if(argc == 2) {
      TSP::AdjacencyMatrix adjMatrix(std::stoi(argv[1]));
      adjMatrix.exportInstance("adjMatrix.txt");
      return 0;
    }
    if(argc != 3)
        throw std::length_error("2 arguments required\nExecution: ./TSP filename maxSeconds\n");
    float maxSeconds = std::stoi(argv[2]);
    std::map<std::string, double> timeMap = howMuchTime(true);
    try {
      unsigned maxSize = std::stoi(argv[1]);
      std::cout << "  Size           Brute Force Cost/Time           Greedy Cost/Time                Dynamic Cost/Time\n";
      for(unsigned i = 2; i <= maxSize; ++i) {
        TSP::AdjacencyMatrix adjMatrix(i);
        printTSP(i, maxSeconds, adjMatrix, timeMap);
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
        printTSP(adjMatrix.numberOfNodes(), maxSeconds, adjMatrix, timeMap);
      }
    }
  }
  catch(std::invalid_argument &e) {
    std::cout << "The second argument should be a number\nExecution: ./TSP filename maxSeconds\n";
  }
}