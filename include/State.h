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

  std::vector<std::tuple<int, int, int> > generateCandidatePairsAtDepth(int d);

  // Add a pair to te current state
  // This means that we map vertex n in G1 to m in G2
  void addPair(int n, int m, int depth);

  void removePair(int i, int m, int depth);

  void restoreStateToDepth(int d);

  std::vector<int> getMapping();

  bool checkMatch();

  int getDepth() { return depth; }

private:
  std::vector<std::pair<int, int> > generateUnfilteredPairs();
  bool r_pred(int n, int m);
  bool r_succ(int n, int m);
  bool r_in(int n, int m);
  bool r_out(int n, int m);
  bool r_new(int n, int m);
  bool F_pred(int n, int m);

  Graph &_G1;
  Graph &_G2;
  int currentlyMatched;
  std::vector<std::pair<int, int> > core_1;
  std::vector<std::pair<int, int> > core_2;
  std::vector<int> in_1;
  std::vector<int> in_2;
  std::vector<int> out_1;
  std::vector<int> out_2;
  int NULL_NODE = -1;
  int depth = 0;
};
