#include <iostream>
#include <vector>
#include <time.h>
#include <string>

#include "GreedyTravellingSalesman.h"
#include "RudeTravellingSalesman.h"
#include "menuUtility.h"

int main() {
  TSP::AdjacencyMatrix a("10.txt");
  //a.exportInstance("b.txt");
  TSP::RTS rudeTSP;
  //std::vector<std::string> path = rudeTSP.Solve(a, "a", "d");
  std::vector<std::string> path = rudeTSP.Solve(a, "c", "c");
  for(unsigned i = 0; i < path.size(); ++i) {
    std::cout << path[i] << ' ';
  }
  std::cout << '\n' << a.pathWeight(path) << '\n';
}