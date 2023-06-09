#include <cstring>
#include <iostream>
#include <queue>

#include "../utils/psvn.hpp"

using namespace std;

// breadth first search for implicit graph (tree)
Node *breadth_first_search(state_t *initial_state) {
  // initialization
  std::queue<Node *> q;
  if (initial_state == nullptr) {
    // initial_state = init();
    return nullptr;
  }
  Node *root = make_root_node(initial_state);
  q.push(root);
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
    for (auto successor : *successors_list) {
      Node *child = make_node(node, successor.first, successor.second);
      q.push(child);
    }
  }
  return nullptr;  // no solution found
}