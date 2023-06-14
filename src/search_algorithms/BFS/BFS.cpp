#include <algorithm>
#include <atomic>
#include <cstring>
#include <iostream>
#include <queue>

#include "../../utils/psvn.hpp"

using namespace std;

// breadth first search for implicit graph (tree)
Node *breadth_first_search(state_t *initial_state,
                           atomic<int> *num_generated_states,
                           atomic<int> *num_expanded_states,
                           atomic<int> *max_depth) {
  // initialization
  std::queue<Node *> q;
  if (initial_state == nullptr) {
    // initial_state = init();
    cout << "Initial state is null" << endl;
    return nullptr;
  }
  Node *root = make_root_node(initial_state);
  q.push(root);
  num_generated_states->fetch_add(1);
  int i = 0;
  // search
  while (!q.empty()) {
    Node *node = q.front();
    q.pop();
    if (isGoal(node->state)) {
      cout << "Solution found!" << endl;
      return node;
    }
    vector<pair<state_t *, Action>> *successors_list = successors(node->state);
    if (successors == nullptr) {
      cout << "Out of memory" << endl;
      return nullptr;
    }
    num_expanded_states->fetch_add(1);
    for (auto successor : *successors_list) {
      Node *child = make_node(node, successor.first, successor.second);
      (*max_depth) = max(max_depth->load(), child->depth);
      q.push(child);
      num_generated_states->fetch_add(1);
    }
  }
  return nullptr;  // no solution found
}