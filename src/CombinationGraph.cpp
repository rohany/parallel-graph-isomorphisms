#include <string>
#include <fstream>
#include <iostream>

#include "Graph.h"
#include "CombinationGraph.h"

// A 2-d vector might be a good solution here:
// one for the in neighbors or something, one for the
// out neighbors. Can return pointers to the vectors
// in the functions for easy use.

/*
 * For simplicities sake while testing,
 * use the following graph format :
 *
 * nodes are from 0 to n-1
 * numNodes
 * node1 node2 #this is an edge
 * i j
 * k l
 * ...
 */
CombinationGraph::CombinationGraph(std::string filename) {

  // OPEN FILE
  std::ifstream infile;
  infile.open(filename.c_str());

  infile >> _numNodes;

  _inNeighbors = std::vector<std::vector<int> >(_numNodes);
  _outNeighbors = std::vector<std::vector<int> >(_numNodes);
  _adjListIn = std::vector<std::vector<int> >(_numNodes);
  _adjListOut = std::vector<std::vector<int> >(_numNodes);
  for (int i = 0; i < _numNodes; i++) {
    _inNeighbors[i] = std::vector<int>(_numNodes);
    _outNeighbors[i] = std::vector<int>(_numNodes);
  }

  int i, j;
  while (infile >> i >> j) {
    addEdge(i, j);
  }
}

void CombinationGraph::printGraph() {
  for (int i = 0; i < _numNodes; i++) {
    std::cout << "In edges of node " << i << ": " << std::endl;
    for (int j = 0; j < _numNodes; j++) {
      if (isEdge(j, i)) {
        std::cout << j << " ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  for (int i = 0; i < _numNodes; i++) {
    std::cout << "Out edges of node " << i << ": " << std::endl;
    for (int j = 0; j < _numNodes; j++) {
      if (isEdge(i, j)) {
        std::cout << j << " ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

/*
 * Adds an edge from node i to node j
 * Requires the inner vectors are set up
 */
void CombinationGraph::addEdge(int i, int j) {
  _inNeighbors[j][i] = 1;
  _outNeighbors[i][j] = 1;

  _adjListIn[j].push_back(i);
  _adjListOut[i].push_back(j);
}

bool CombinationGraph::isEdge(int i, int j) { return _outNeighbors[i][j]; }

std::vector<int> &CombinationGraph::getPredecessors(int i) {
  return _adjListIn[i];
}

std::vector<int> &CombinationGraph::getSuccessors(int i) {
  return _adjListOut[i];
}

int CombinationGraph::getNumNodes() { return _numNodes; }
