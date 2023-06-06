#include <iostream>
#include <queue>

#include "../utils/psvn.h++"

using namespace std;

// breadth first search for implicit graph (tree)
Node *breadth_first_search(state_t *initial_state) {
  // initialization
  std::queue<Node *> q;
  if (initial_state == NULL) {
    // initial_state = init();
    return NULL;
  }
  Node *root = make_root_node(initial_state);
  q.push(root);

  // search
  while (!q.empty()) {
    Node *node = q.front();
    q.pop();
    if (is_goal(node->state)) {
      cout << "Solution found!" << endl;
      return node;
    }
    vector<pair<state_t *, Action>> *successors_list = successors(node->state);
    for (auto successor : *successors_list) {
      Node *child = make_node(node, successor.first, successor.second);
      q.push(child);
    }
  }
  return NULL;  // no solution found
}