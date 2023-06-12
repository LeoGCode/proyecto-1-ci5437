#include "psvn.hpp"

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
  node->g = parent->g + getFwdRuleCost(action);
  return node;
}

void oprint_state(state_t *state) {
  char *str_state = new char[1024];
  sprintState(str_state, 1024, state);
  cout << str_state << endl;
}

vector<pair<state_t *, Action>> *successors(state_t *state) {
  vector<pair<state_t *, Action>> *successors_list =
      new vector<pair<state_t *, Action>>;
  ruleid_iterator_t *iter = new ruleid_iterator_t;
  int move_cost, ruleid;
  int hist, child_hist;
  hist = initHistory();
  initFwdIter(iter, state);
  while ((ruleid = nextRuleid(iter)) >= 0) {
    if (!fwdRuleValidForHistory(hist, ruleid)) {
      continue;
    }
    state_t *child = (state_t *)(malloc(sizeof(state_t)));
    if (child == NULL) {
      fprintf(stderr, "out of memory\n");
      exit(-1);
    }
    child_hist = nextFwdHistory(hist, ruleid);
    applyFwdRule(ruleid, state, child);
    //  oprint_state(child);
    //     move_cost = get_fwd_rule_cost(ruleid);
    successors_list->push_back(make_pair(child, ruleid));
  }
  free(iter);
  return successors_list;
}
