#include <iostream>
#include <assert.h>
#include <vector>

#include "CombinationGraph.h"

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cout << "Please supply a file name" << std::endl;
    return 0;
  }
  CombinationGraph graph = CombinationGraph(argv[1]);
  Graph &G1 = graph;
  G1.printGraph();

  /*
  assert(G1.isEdge(0, 1));
  assert(G1.isEdge(1, 3));
  assert(G1.isEdge(0, 2));
  assert(G1.isEdge(2, 3));
  assert(!G1.isEdge(1, 0));
  */

  return 0;
}
