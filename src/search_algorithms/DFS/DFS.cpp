#include <atomic>
#include <cstring>
#include <iostream>

#include "../../utils/psvn.hpp"

using namespace std;

Node *dfs_visit(Node *n, atomic<int> *num_generated_states,
                atomic<int> *num_expanded_states) {
  // print node pointer
  cout << "Node pointer: " << n
       << " Num generated states: " << num_generated_states->load() << endl;
  if (num_generated_states->load() == 43665) {
    cout << "Num generated states: " << num_generated_states->load() << endl;
  }
  if (isGoal(n->state)) {
    cout << "Solution found!" << endl;
    return n;
  }
  vector<pair<state_t *, Action>> *successors_list = successors(n->state);
  num_expanded_states->fetch_add(1);
  for (auto successor : *successors_list) {
    Node *child = make_node(n, successor.first, successor.second);
    num_generated_states->fetch_add(1);
    Node *result = dfs_visit(child, num_generated_states, num_expanded_states);
    if (result != nullptr) {
      return result;
    }
  }
  return nullptr;  // no solution found
}

// depth first search for implicit graph (tree)
Node *depth_first_search(state_t *initial_state,
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
  // search
  return dfs_visit(root, num_generated_states, num_expanded_states);
}
