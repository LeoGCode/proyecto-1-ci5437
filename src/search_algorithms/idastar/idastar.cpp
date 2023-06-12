#include "idastar.hpp"

#include <limits.h>

#define INFINITY UINT_MAX

pair<Node *, unsigned> f_bounded_dfs_visit(Node *node, unsigned bound,
                                           heuristic_t heuristic,
                                           atomic<int> *num_generated_states,
                                           atomic<int> *num_expanded_states) {
  // bases cases
  auto f = node->g + heuristic(node->state);
  if (f > bound) {
    return make_pair(nullptr, f);
  }
  if (isGoal(node->state)) {
    return make_pair(node, node->g);
  }

  auto t = INFINITY;
  vector<pair<state_t *, Action>> *successors_list = successors(node->state);
  num_expanded_states->fetch_add(1);
  for (auto successor : *successors_list) {
    Node *child = make_node(node, successor.first, successor.second);
    num_generated_states->fetch_add(1);
    auto result = f_bounded_dfs_visit(
        child, bound, heuristic, num_generated_states, num_expanded_states);
    if (result.first != nullptr) {
      return result;
    }
    t = min(t, result.second);
  }
  return make_pair(nullptr, t);
}

Node *idastar_search(state_t *initial_state, heuristic_t heuristic,
                     atomic<int> *num_generated_states,
                     atomic<int> *num_expanded_states) {
  Node *root = make_root_node(initial_state);
  unsigned bound = heuristic(initial_state);
  // search with increasing bounds
  while (true) {
    pair<Node *, unsigned> result = f_bounded_dfs_visit(
        root, bound, heuristic, num_generated_states, num_expanded_states);
    if (result.first != nullptr) {
      return result.first;
    }
    bound = result.second;
  }
}
