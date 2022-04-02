#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <thread>
#include <chrono> 

#include "GreedyTravellingSalesman.h"
#include "RudeTravellingSalesman.h"
#include "DynamicTravellingSalesman.h"
#include "menuUtility.h"

void timer(TSP::TravellingSalesman& tsp)
{
  std::this_thread::sleep_for (std::chrono::seconds(60));
  tsp.stop = true;
}

int main() {
  for(unsigned i = 3; i < 16; ++i) {
    TSP::AdjacencyMatrix adjMatrix(i);
    std::string size_str = std::to_string(i);
    int size_size = size_str.size();
    std::cout << " | " << *(new std::string((6 - size_size) / 2, ' ')) <<
    " " << size_str <<
    *(new std::string((6 - size_size) / 2 + (6 - size_size) % 2, ' ')) << " |-> ";

    TSP::RTS rudeTSP = *new TSP::RTS();
    std::thread r (timer, std::ref(rudeTSP));
    clock_t t_start_r = clock();
    int costR = adjMatrix.pathWeight(rudeTSP.Solve(adjMatrix, adjMatrix.convertNode(2)));
    double clock_r = (double)(clock() - t_start_r)/CLOCKS_PER_SEC;
    std::string clock_r_str = std::to_string((double)(clock() - t_start_r)/CLOCKS_PER_SEC);
    int clock_r_size = clock_r_str.size();
    std::cout << *(new std::string((12 - clock_r_size) / 2, ' ')) <<
    " " << clock_r_str <<
    *(new std::string((12 - clock_r_size) / 2 + (12 - clock_r_size) % 2, ' ')) << " | ";
    std::string costR_str = std::to_string(costR);
    std::cout << *(new std::string((12 - costR_str.size()) / 2, ' ')) <<
    " " << costR_str <<
    *(new std::string((12 - costR_str.size()) / 2 + (12 - costR_str.size()) % 2, ' ')) << " | ";

    TSP::GTS greedyTSP = *new TSP::GTS();
    std::thread g (timer, std::ref(greedyTSP));    
    clock_t t_start_g = clock();
    int costG = adjMatrix.pathWeight(greedyTSP.Solve(adjMatrix, adjMatrix.convertNode(2)));
    double clock_g = (double)(clock() - t_start_g)/CLOCKS_PER_SEC;
    std::string clock_g_str = std::to_string(clock_g);
    int clock_g_size = clock_g_str.size();
    std::cout << *(new std::string((12 - clock_g_size) / 2, ' ')) <<
    " " << clock_g_str <<
    *(new std::string((12 - clock_g_size) / 2 + (12 - clock_g_size) % 2, ' ')) << " | ";
    std::string costG_str = std::to_string(costG);
    std::cout << *(new std::string((12 - costG_str.size()) / 2, ' ')) <<
    " " << costG_str <<
    *(new std::string((12 - costG_str.size()) / 2 + (12 - costG_str.size()) % 2, ' ')) << " | ";

    TSP::DTS dynamicTSP = *new TSP::DTS();
    std::thread d (timer, std::ref(dynamicTSP));
    clock_t t_start_d = clock();
    int costD = adjMatrix.pathWeight(dynamicTSP.Solve(adjMatrix, adjMatrix.convertNode(2)));
    double clock_d = (double)(clock() - t_start_d)/CLOCKS_PER_SEC;
    std::string clock_d_str = std::to_string(clock_d);
    int clock_d_size = clock_d_str.size();
    std::cout << *(new std::string((12 - clock_d_size) / 2, ' ')) <<
    " " << clock_d_str <<
    *(new std::string((12 - clock_d_size) / 2 + (12 - clock_d_size) % 2, ' ')) << " | ";
    std::string costD_str = std::to_string(costD);
    std::cout << *(new std::string((12 - costD_str.size()) / 2, ' ')) <<
    " " << costD_str <<
    *(new std::string((12 - costD_str.size()) / 2 + (12 - costD_str.size()) % 2, ' ')) << " | ";

    g.detach();
    r.detach();
    d.detach();
    std::cout << '\n';
  }
  //a.exportInstance("b.txt");
   TSP::AdjacencyMatrix a(4);
   TSP::RTS rudeTSP;
  TSP::DTS dynamicTSP;
  std::vector<std::string> path2 = dynamicTSP.Solve(a, a.convertNode(2));
  std::vector<std::string> path1 = rudeTSP.Solve(a, a.convertNode(2));
  std::vector<std::string> path = rudeTSP.Solve(a, "x");
  for(unsigned i = 0; i < path1.size(); ++i) {
    std::cout << path1[i] << ' ';
  }
  std::cout << '\n';
  for(unsigned i = 0; i < path2.size(); ++i) {
    std::cout << path2[i] << ' ';
  }
  //a.exportInstance("4.txt");
  std::cout << '\n' << a.pathWeight(path1) << '\n';
  std::cout << '\n' << a.pathWeight(path2) << '\n';
}