#include "psvn.h++"

#include <iostream>
#include <queue>

using namespace std;

Node *make_root_node(state_t *state) {
  Node *node = new Node;
  node->state = state;
  node->parent = NULL;
  node->action = -1;
  node->g = 0;
  return node;
}

Node *make_node(Node *parent, state_t *state, Action action) {
  Node *node = new Node;
  node->state = state;
  node->parent = parent;
  node->action = action;
  node->g = parent->g + get_fwd_rule_cost(action);
  return node;
}

vector<pair<state_t *, Action>> *successors(state_t *state) {
  vector<pair<state_t *, Action>> *successors_list =
      new vector<pair<state_t *, Action>>;
  state_t *child;
  ruleid_iterator_t *iter;
  int move_cost, ruleid;
  init_fwd_iter(iter, state);
  while ((ruleid = next_ruleid(iter)) >= 0) {
    apply_fwd_rule(ruleid, state, child);
    // move_cost = get_fwd_rule_cost(ruleid);
    successors_list->push_back(make_pair(child, ruleid));
  }
  return successors_list;
}
