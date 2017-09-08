#pragma once

#include <vector>
#include <tuple>
#include "Graph.h"

/*
 * A class to keep track of the state in the VF2 algorithm.
 */

class State {

public:
  // Maybe need to change the parameters here
  State(Graph &G1, Graph &G2);

  // Generate possible pairs
  std::vector<std::pair<int, int> > generateCandidatePairs();

  // Add a pair to te current state
  // This means that we map vertex n in G1 to m in G2
  void addPair(int n, int m);

private:
  Graph &_G1;
  Graph &_G2;
  std::vector<int> core_1;
  std::vector<int> core_2;
  int NULL_NODE = -1;

  // need the ins, outs?
};
