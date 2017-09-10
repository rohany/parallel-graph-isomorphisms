#pragma once

#include <tuple>
#include <vector>

#include "Graph.h"
#include "State.h"

/*
 * Main driver class for the matching code. Use this
 * class to create a matcher object to match two
 * graphs.
 */

class Matcher {

public:
  Matcher(Graph &G1, Graph &G2);

  // Will return a mapping of G1's vertices to G2's vertices
  // if the graphs are isomorphic, else return the equivalent
  // of NONE
  std::pair<bool, std::vector<int> > match();

private:
  // recursive matcher
  // TODO: decide whether a reference or copy is best here
  std::pair<bool, std::vector<int> > rec_match(State s);

  Graph &_G1;
  Graph &_G2;
  State startState;
};
