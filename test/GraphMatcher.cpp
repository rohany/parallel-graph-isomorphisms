#include <iostream>
#include <tuple>
#include <vector>

#include "CombinationGraph.h"
#include "Matcher.h"
#include "Graph.h"

int main(int argc, char **argv) {

  if (argc < 3) {
    std::cout << "Please submit two graph files for matching!" << std::endl;
    return 0;
  }

  CombinationGraph graph1(argv[1]);
  CombinationGraph graph2(argv[2]);

  Graph &G1 = graph1;
  Graph &G2 = graph2;

  Matcher isoMatcher(G1, G2);

  auto result = isoMatcher.match();

  std::cout << result.first << std::endl;
}
