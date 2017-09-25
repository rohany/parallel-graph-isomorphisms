#include <tuple>
#include <vector>
#include <algorithm>

#include "State.h"
#include "Graph.h"

State::State(Graph &G1, Graph &G2) : _G1(G1), _G2(G2), currentlyMatched(0) {
  // Either want to allocate these in parallel, or
  // allow match to take in a starting state to push
  // off the time of allocation for these
  core_1 = std::vector<std::pair<int, int> >(_G1.getNumNodes(),
                                             std::pair<int, int>(NULL_NODE, 0));
  core_2 = std::vector<std::pair<int, int> >(_G2.getNumNodes(),
                                             std::pair<int, int>(NULL_NODE, 0));
  in_1 = std::vector<int>(_G1.getNumNodes(), NULL_NODE);
  in_2 = std::vector<int>(_G1.getNumNodes(), NULL_NODE);
  out_1 = std::vector<int>(_G1.getNumNodes(), NULL_NODE);
  out_2 = std::vector<int>(_G1.getNumNodes(), NULL_NODE);
}

bool State::r_pred(int n, int m) {
  // calculate intersection of current mapping and in neighbors of N
  bool first_and = true;
  for (int i = 0; i < _G1.getNumNodes(); i++) {
    int n_prime = core_1[i].first;
    if (n_prime != NULL_NODE && _G1.isEdge(i, n)) {
      // show there is an m' in pred of M that it works
      auto m_preds = _G2.getPredecessors(m);
      bool found = false;
      for (auto j : m_preds) {
        if (j == n_prime) {
          found = true;
        }
      }
      first_and &= found;
    }
  }
  bool second_and = true;
  for (int i = 0; i < _G2.getNumNodes(); i++) {
    int m_prime = core_2[i].first;
    if (m_prime != NULL_NODE && _G2.isEdge(i, m)) {
      // show there is an m' in pred of M that it works
      auto n_preds = _G1.getPredecessors(n);
      bool found = false;
      for (auto j : n_preds) {
        if (j == m_prime) {
          found = true;
        }
      }
      second_and &= found;
    }
  }
  return first_and && second_and;
}
// can be combined with r_pred for efficiency
bool State::r_succ(int n, int m) {
  // calculate intersection of current mapping and in neighbors of N
  bool first_and = true;
  for (int i = 0; i < _G1.getNumNodes(); i++) {
    int n_prime = core_1[i].first;
    if (n_prime != NULL_NODE && _G1.isEdge(n, i)) {
      // show there is an m' in pred of M that it works
      auto m_succs = _G2.getSuccessors(m);
      bool found = false;
      for (auto j : m_succs) {
        if (j == n_prime) {
          found = true;
        }
      }
      first_and &= found;
    }
  }
  bool second_and = true;
  for (int i = 0; i < _G2.getNumNodes(); i++) {
    int m_prime = core_2[i].first;
    if (m_prime != NULL_NODE && _G2.isEdge(m, i)) {
      // show there is an m' in pred of M that it works
      auto n_succs = _G1.getSuccessors(n);
      bool found = false;
      for (auto j : n_succs) {
        if (j == m_prime) {
          found = true;
        }
      }
      second_and &= found;
    }
  }
  return first_and && second_and;
}
bool State::r_in(int n, int m) {
  // size of in sets need to be same
  int n_count = 0;
  int m_count = 0;
  auto n_succ = _G1.getSuccessors(n);
  auto m_succ = _G2.getSuccessors(m);
  auto n_pred = _G1.getPredecessors(n);
  auto m_pred = _G2.getPredecessors(m);

  for (auto i : n_succ) {
    if (in_1[i] != NULL_NODE) {
      n_count++;
    }
  }
  for (auto i : m_succ) {
    if (in_2[i] != NULL_NODE) {
      m_count++;
    }
  }
  if (m_count != n_count) {
    return false;
  }

  n_count = 0;
  m_count = 0;

  for (auto i : n_pred) {
    if (in_1[i] != NULL_NODE) {
      n_count++;
    }
  }
  for (auto i : m_pred) {
    if (in_2[i] != NULL_NODE) {
      m_count++;
    }
  }
  if (m_count != n_count) {
    return false;
  }
  return true;
}
bool State::r_out(int n, int m) {
  int n_count = 0;
  int m_count = 0;
  auto n_succ = _G1.getSuccessors(n);
  auto m_succ = _G2.getSuccessors(m);
  auto n_pred = _G1.getPredecessors(n);
  auto m_pred = _G2.getPredecessors(m);

  for (auto i : n_succ) {
    if (out_1[i] != NULL_NODE) {
      n_count++;
    }
  }
  for (auto i : m_succ) {
    if (out_2[i] != NULL_NODE) {
      m_count++;
    }
  }
  if (m_count != n_count) {
    return false;
  }

  n_count = 0;
  m_count = 0;

  for (auto i : n_pred) {
    if (out_1[i] != NULL_NODE) {
      n_count++;
    }
  }
  for (auto i : m_pred) {
    if (out_2[i] != NULL_NODE) {
      m_count++;
    }
  }
  if (m_count != n_count) {
    return false;
  }
  return true;
}
bool State::r_new(int n, int m) {
  // size of unmatched nodes in the not in the in or out frontier
  auto n_succ = _G1.getSuccessors(n);
  auto m_succ = _G2.getSuccessors(m);
  auto n_pred = _G1.getPredecessors(n);
  auto m_pred = _G2.getPredecessors(m);
  int n_count = 0;
  int m_count = 0;
  for (auto i : n_succ) {
    if (in_1[i] == NULL_NODE && out_1[i] == NULL_NODE) {
      n_count++;
    }
  }
  for (auto i : m_succ) {
    if (in_2[i] == NULL_NODE && out_2[i] == NULL_NODE) {
      m_count++;
    }
  }
  if (n_count != m_count) {
    return false;
  }
  n_count = 0;
  m_count = 0;
  for (auto i : n_pred) {
    if (in_1[i] == NULL_NODE && out_1[i] == NULL_NODE) {
      n_count++;
    }
  }
  for (auto i : m_pred) {
    if (in_2[i] == NULL_NODE && out_2[i] == NULL_NODE) {
      m_count++;
    }
  }
  if (n_count != m_count) {
    return false;
  }
  return true;
}

// probably more efficient way to do this with than calling each one,
// but for now, we can just call each of them.
bool State::F_pred(int n, int m) {
  return r_pred(n, m) && r_succ(n, m) && r_in(n, m) && r_out(n, m) &&
         r_new(n, m);
}

std::vector<std::pair<int, int> > State::generateUnfilteredPairs() {
  // loop through all the vertices in the in / out sets of the
  // G2, like the paper says, and generate all the pairs.

  // apply the check to remove the m_j values if larger in here,
  // as opposed to applying the possibly expensive feasability
  // rules to uneccesary elements.

  std::vector<std::pair<int, int> > result;

  for (int i = 0; i < _G1.getNumNodes(); i++) {
    for (int j = 0; j < _G2.getNumNodes(); j++) {
      if ((in_1[i] != NULL_NODE || out_1[i] != NULL_NODE) &&
          core_1[i].first == NULL_NODE &&
          (in_2[j] != NULL_NODE || out_2[j] != NULL_NODE) &&
          core_2[j].first == NULL_NODE) {
        result.push_back(std::pair<int, int>(i, j));
        break;
      }
    }
  }

  if (result.size() != 0) {
    return result;
  }

  // if we didnt generate any - hacky way of adding alot of pairs
  for (int i = 0; i < _G1.getNumNodes(); i++) {
    for (int j = 0; j < _G2.getNumNodes(); j++) {
      if (core_1[i].first == NULL_NODE && core_2[j].first == NULL_NODE) {
        result.push_back(std::pair<int, int>(i, j));
        break;
      }
    }
  }

  return result;
}

std::vector<std::pair<int, int> > State::generateCandidatePairs() {

  auto possiblePairs = generateUnfilteredPairs();

  auto filtered = std::remove_if(
      possiblePairs.begin(), possiblePairs.end(),
      [&](std::pair<int, int> x) { return !F_pred(x.first, x.second); });
  // filtered array
  possiblePairs.erase(filtered, possiblePairs.end());
  return possiblePairs;
}

std::vector<std::tuple<int, int, int> >
State::generateCandidatePairsAtDepth(int d) {
  auto mid = generateCandidatePairs();
  std::vector<std::tuple<int, int, int> > res;

  for (auto i : mid) {
    res.push_back(std::tuple<int, int, int>(i.first, i.second, d));
  }

  return res;
}

void State::restoreStateToDepth(int d) {

  depth = d;

  for (int i = 0; i < _G1.getNumNodes(); i++) {
    if (in_1[i] >= d) {
      in_1[i] = NULL_NODE;
    }
    if (in_2[i] >= d) {
      in_2[i] = NULL_NODE;
    }
    if (out_1[i] >= d) {
      out_1[i] = NULL_NODE;
    }
    if (out_2[i] >= d) {
      out_2[i] = NULL_NODE;
    }
    if (core_1[i].first != NULL_NODE && core_1[i].second >= d) {
      core_1[i] = std::pair<int, int>(NULL_NODE, d);
      currentlyMatched--;
    }
    if (core_2[i].first != NULL_NODE && core_2[i].second >= d) {
      core_2[i] = std::pair<int, int>(NULL_NODE, d);
    }
  }
}

bool State::checkMatch() {

  if (currentlyMatched != _G1.getNumNodes()) {
    return false;
  }

  // Can be a pfor
  for (int i = 0; i < _G1.getNumNodes(); i++) {
    auto n1 = _G1.getPredecessors(i);
    auto n2 = _G2.getPredecessors(core_1[i].first);

    if (n1.size() != n2.size()) {
      return false;
    }

    for (int j = 0; j < (int)n1.size(); j++) {
      int v = core_1[n1[j]].first;
      if (!std::binary_search(n2.begin(), n2.end(), v)) {
        return false;
      }
    }

    n1 = _G1.getSuccessors(i);
    n2 = _G2.getSuccessors(core_1[i].first);

    if (n1.size() != n2.size()) {
      return false;
    }

    for (int j = 0; j < (int)n1.size(); j++) {
      int v = core_1[n1[j]].first;
      if (!std::binary_search(n2.begin(), n2.end(), v)) {
        return false;
      }
    }
  }
  return true;
}

std::vector<int> State::getMapping() {

  std::vector<int> res;
  for (auto i : core_1) {
    res.push_back(i.first);
  }
  return res;
}

// TODO: figure out depth interaction with this code
void State::addPair(int n, int m, int d) {
  core_1[n] = std::pair<int, int>(m, d);
  core_2[m] = std::pair<int, int>(n, d);

  in_1[n] = d;
  in_2[m] = d;
  out_1[n] = d;
  out_2[m] = d;
  currentlyMatched++;
  depth = d;

  /*
   * Add logic for updating in and out sets
   */

  for (const auto &i : _G1.getPredecessors(n)) {
    // if adding level, then would need to
    // check if level exists first
    if (in_1[i] == NULL_NODE) {
      in_1[i] = d;
    }
  }

  for (const auto &i : _G1.getSuccessors(n)) {
    // same as above
    if (out_1[i] == NULL_NODE) {
      out_1[i] = d;
    }
  }

  for (const auto &i : _G2.getPredecessors(m)) {
    // if adding level, then would need to
    // check if level exists first
    if (in_2[i] == NULL_NODE) {
      in_2[i] = d;
    }
  }

  for (const auto &i : _G2.getSuccessors(m)) {
    // same as above
    if (out_2[i] == NULL_NODE) {
      out_2[i] = d;
    }
  }
}

void State::removePair(int n, int m, int depth) {

  // depth interaction here?
  core_1[n] = std::pair<int, int>(NULL_NODE, 0);
  core_2[m] = std::pair<int, int>(NULL_NODE, 0);
  currentlyMatched--;

  if (in_1[n] == depth) {
    in_1[n] = NULL_NODE;
  }
  if (in_2[m] == depth) {
    in_2[m] = NULL_NODE;
  }
  if (out_1[n] == depth) {
    out_1[n] = NULL_NODE;
  }
  if (out_2[m] == depth) {
    out_2[m] = NULL_NODE;
  }

  for (const auto &i : _G1.getPredecessors(n)) {
    if (in_1[i] == depth) {
      in_1[i] = NULL_NODE;
    }
  }
  for (const auto &i : _G1.getSuccessors(n)) {
    if (out_1[i] == depth) {
      out_1[i] = NULL_NODE;
    }
  }

  for (const auto &i : _G2.getPredecessors(m)) {
    if (in_2[i] == depth) {
      in_2[i] = NULL_NODE;
    }
  }
  for (const auto &i : _G2.getSuccessors(m)) {
    if (out_2[i] == depth) {
      out_2[i] = NULL_NODE;
    }
  }
}
