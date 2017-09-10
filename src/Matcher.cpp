#include <tuple>
#include <vector>

#include "Matcher.h"
#include "Graph.h"
#include "State.h"

Matcher::Matcher(Graph &G1, Graph &G2) : _G1(G1), _G2(G2), startState(G1, G2) {}

std::pair<bool, std::vector<int> > Matcher::match() {

  if (_G1.getNumNodes() != _G2.getNumNodes()) {
    return std::pair<bool, std::vector<int> >(false, {});
  }

  return rec_match(startState);
}

std::pair<bool, std::vector<int> > Matcher::rec_match(State s) {

  if (s.checkMatch()) {
    return std::pair<bool, std::vector<int> >(true, s.getMapping());
  }

  auto candidatePairs = s.generateCandidatePairs();

  // parallel for
  for (auto &p : candidatePairs) {
    s.addPair(p.first, p.second);

    auto res = rec_match(s);
    if (res.first) {
      return res;
    }
    // restore data structure??
  }

  return std::pair<int, std::vector<int> >(false, {});
}
