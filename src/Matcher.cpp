#include <tuple>
#include <vector>
#include <stack>

#include "Matcher.h"
#include "Graph.h"
#include "State.h"

Matcher::Matcher(Graph &G1, Graph &G2) : _G1(G1), _G2(G2), startState(G1, G2) {}

std::pair<bool, std::vector<int> > Matcher::match() {

  if (_G1.getNumNodes() != _G2.getNumNodes()) {
    return std::pair<bool, std::vector<int> >(false, {});
  }

  // return rec_match(startState, 0);
  return stack_match();
}

std::pair<bool, std::vector<int> > Matcher::rec_match(State s, int depth) {

  if (s.checkMatch()) {
    return std::pair<bool, std::vector<int> >(true, s.getMapping());
  }

  auto candidatePairs = s.generateCandidatePairs();

  // parallel for
  for (auto &p : candidatePairs) {
    s.addPair(p.first, p.second, depth);

    auto res = rec_match(s, depth + 1);
    if (res.first) {
      return res;
    }

    s.removePair(p.first, p.second, depth);
  }

  return std::pair<bool, std::vector<int> >(false, {});
}

std::pair<bool, std::vector<int> > Matcher::stack_match() {

  std::stack<std::tuple<int, int, int> > frontier;
  auto starting_states = startState.generateCandidatePairsAtDepth(1);

  for (auto i : starting_states) {
    frontier.push(i);
  }

  while (!frontier.empty()) {

    if (startState.checkMatch()) {
      return std::pair<bool, std::vector<int> >(true, startState.getMapping());
    }
    int n, m, d;
    std::tie(n, m, d) = frontier.top();
    frontier.pop();

    int curDepth = startState.getDepth();
    if (curDepth <= d) {
      startState.restoreStateToDepth(d);
    }
    startState.addPair(n, m, d);

    auto new_pairs = startState.generateCandidatePairsAtDepth(d + 1);

    for (auto i : new_pairs) {
      frontier.push(i);
    }
  }

  if (startState.checkMatch()) {
    return std::pair<bool, std::vector<int> >(true, startState.getMapping());
  }
  return std::pair<bool, std::vector<int> >(false, {});
}
