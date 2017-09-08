#include <tuple>
#include <vector>

#include "State.h"
#include "Graph.h"

State::State(Graph &G1, Graph &G2) : _G1(G1), _G2(G2), currentlyMatched(0) {
  // Either want to allocate these in parallel, or
  // allow match to take in a starting state to push
  // off the time of allocation for these
  core_1 = std::vector<int>(_G1.getNumNodes(), NULL_NODE);
  core_2 = std::vector<int>(_G2.getNumNodes(), NULL_NODE);
  in_1 = std::vector<int>(_G1.getNumNodes(), NULL_NODE);
  in_2 = std::vector<int>(_G1.getNumNodes(), NULL_NODE);
  out_1 = std::vector<int>(_G1.getNumNodes(), NULL_NODE);
  out_2 = std::vector<int>(_G1.getNumNodes(), NULL_NODE);
}

std::vector<std::pair<int, int> > State::generateCandidatePairs() {
  return {};
}

bool State::checkMatch() {
  if (currentlyMatched != _G1.getNumNodes()) {
    return false;
  }

  // matcher code

  for (int i = 0; i < _G1.getNumNodes(); i++) {
    // wei
  }
}

// maybe need to hold state level?
void State::addPair(int n, int m) {

  core_1[n] = m;
  core_2[m] = n;

  // REPLACE THIS LATER WITH LEVEL OF SEARCH
  in_1[n] = 1;
  in_2[m] = 1;
  out_1[n] = 1;
  out_2[m] = 1;

  /*
   * Add logic for updating in and out sets
   */

  for (const auto &i : _G1.getPredecessors(n)) {
    // if adding level, then would need to
    // check if level exists first
    in_1[i] = 1;
  }
  for (const auto &i : _G1.getSuccessors(n)) {
    // same as above
    out_1[i] = 1;
  }

  for (const auto &i : _G2.getPredecessors(n)) {
    // if adding level, then would need to
    // check if level exists first
    in_2[i] = 1;
  }
  for (const auto &i : _G2.getSuccessors(n)) {
    // same as above
    out_2[i] = 1;
  }
}
