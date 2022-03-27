#include <iostream>
#include <vector>
#include <time.h>
#include <string>

#include "TravellingSalesman.h"
#include "menuUtility.h"

int main() {
  TSP::AdjacencyMatrix a(100);
  a.exportInstance("b.txt");
}