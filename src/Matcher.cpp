#include <tuple>
#include <vector>

#include "Matcher.h"
#include "Graph.h"
#include "State.h"

Matcher::Matcher(Graph &G1, Graph &G2) : _G1(G1), _G2(G2) {
  // placeholder
}

std::pair<bool, std::vector<int> > Matcher::match() {
  return std::pair<bool, std::vector<int> >(false, {});
}

bool Matcher::rec_match(State s) {
  (void)s;

  // if state matching covers graph return true

  // else generate all generate all candidate pairs from
  // the state

  // for each possible pair - add pair to state, run rec_match

  // return or of all the results - need the result from the state?
  return false;
}
