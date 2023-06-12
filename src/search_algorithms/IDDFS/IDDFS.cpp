#include <atomic>
#include <iostream>

#include "../../utils/psvn.hpp"

using namespace std;

pair<Node *, unsigned> bounded_dfs_visit(Node *n, unsigned d, unsigned bound,
                                         atomic<int> *num_generated_states,
                                         atomic<int> *num_expanded_states) {
  if (d > bound) {
    return make_pair(nullptr, d);
  }
  if (isGoal(n->state)) {
    cout << "Solution found!" << endl;
    return make_pair(n, bound);
  }
  unsigned t = UINT64_MAX;
  vector<pair<state_t *, Action>> *successors_list = successors(n->state);
  num_expanded_states->fetch_add(1);
  for (auto successor : *successors_list) {
    Node *child = make_node(n, successor.first, successor.second);
    num_generated_states->fetch_add(1);
    pair<Node *, unsigned> p = bounded_dfs_visit(
        child, d + 1, bound, num_generated_states, num_expanded_states);
    if (p.first != nullptr) {
      return p;
    }
    t = min(t, p.second);
  }

  return make_pair(nullptr, t);
}

Node *iterative_deepening_depth_first_search(state_t *initial_state,
                                             atomic<int> *num_generated_states,
                                             atomic<int> *num_expanded_states) {
  // initialization
  if (initial_state == nullptr) {
    // initial_state = init();
    cout << "Initial state is null" << endl;
    return nullptr;
  }
  Node *root = make_root_node(initial_state);
  num_generated_states->fetch_add(1);
  int bound = 0;
  // search
  while (true) {
    pair<Node *, unsigned> p = bounded_dfs_visit(
        root, 0, bound, num_generated_states, num_expanded_states);
    if (p.first != nullptr) {
      return p.first;
    }
    bound = p.second;
  }
}
