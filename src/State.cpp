#include <tuple>
#include <vector>
#include <algorithm>

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

  // Can be a pfor
  for (int i = 0; i < _G1.getNumNodes(); i++) {
    auto n1 = _G1.getPredecessors(i);
    auto n2 = _G2.getPredecessors(core_1[i]);

    if (n1.size() != n2.size()) {
      return false;
    }

    for (int j = 0; j < (int)n1.size(); j++) {
      int v = core_1[n1[j]];
      if (!std::binary_search(n2.begin(), n2.end(), v)) {
        return false;
      }
    }

    n1 = _G1.getSuccessors(i);
    n2 = _G2.getSuccessors(core_1[i]);

    if (n1.size() != n2.size()) {
      return false;
    }

    for (int j = 0; j < (int)n1.size(); j++) {
      int v = core_1[n1[j]];
      if (std::binary_search(n2.begin(), n2.end(), v)) {
        return false;
      }
    }
  }
  return true;
}

std::vector<int> State::getMapping() { return core_1; }

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
