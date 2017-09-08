#pragma once

#include <string>
#include <vector>

#include "Graph.h"

// can do a 2d vector or something here
// can do the neighbors rows compressed into words
// to save space - for now just do rows of 1's
class CombinationGraph : public Graph {

public:
  CombinationGraph(std::string filename);

  bool isEdge(int i, int j);
  std::vector<int> &getPredecessors(int i);
  std::vector<int> &getSuccessors(int i);
  int getNumNodes();

  void printGraph();

private:
  // [i][j] asks is j an in neighbors of i
  std::vector<std::vector<int> > _inNeighbors;
  // [i][j] asks is j an out neighbors of i
  std::vector<std::vector<int> > _outNeighbors;

  // Used for fast iteration over in and out
  // neighbors
  std::vector<std::vector<int> > _adjListIn;
  std::vector<std::vector<int> > _adjListOut;

  // Add an edge from i to j
  void addEdge(int i, int j);

  int _numNodes;
};
