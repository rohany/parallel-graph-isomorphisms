#pragma once

#include <string>
#include <vector>

/*
 * Graph data structure interface. If we allow no modification
 * to this graph data structure, then we can support multiple
 * threads reading the structure without having to implement
 * a form of synchronization on the structure. This class
 * is meant to be extended for a specific graph implementation.
 */

// Maybe stick a const on everything, to get more work done
// by the compiler here

class Graph {

public:
  // Does there exist a directed edge from node i to node j
  virtual bool isEdge(int i, int j) = 0;

  // Having these functions return vectors might
  // induce alot of copying - could return references
  // may also want to use shared pointers here?
  // or just returning a const reference

  // Get in neighbors of node i
  virtual std::vector<int> &getPredecessors(int i) = 0;

  // Get out neighbors of node i
  virtual std::vector<int> &getSuccessors(int i) = 0;

  // Get number of nodes in the graph
  virtual int getNumNodes() = 0;

  // Print the graph, for debugging purposes
  virtual void printGraph() = 0;

  // Do something given a state?
};
