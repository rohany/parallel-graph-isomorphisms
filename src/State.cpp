#include <tuple>
#include <vector>

#include "State.h"
#include "Graph.h"

State::State(Graph &G1, Graph &G2) : _G1(G1), _G2(G2) {
  core_1 = std::vector<int>(_G1.getNumNodes(), NULL_NODE);
  core_2 = std::vector<int>(_G2.getNumNodes(), NULL_NODE);
}

std::vector<std::pair<int, int> > State::generateCandidatePairs() {
  return {};
}

void State::addPair(int n, int m) {
  core_1[n] = m;
  core_2[m] = n;
}
