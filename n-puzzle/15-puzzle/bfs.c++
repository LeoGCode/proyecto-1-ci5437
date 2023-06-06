#include <iostream>
#include <queue>
#include <vector>

#include "15-puzzle.c"

using namespace std;

typedef int Action;

// state_t *init();

typedef struct Node {
  state_t *state;
  struct Node *parent;
  Action action;  // ruleid
  unsigned g;     // cost of partial path
} Node;

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

void oprint_state(state_t *state) {
  char *str_state = new char[256];
  sprint_state(str_state, 256, state);
  cout << str_state << endl;
}

vector<pair<state_t *, Action>> *successors(state_t *state) {
  vector<pair<state_t *, Action>> *successors_list =
      new vector<pair<state_t *, Action>>;
  ruleid_iterator_t *iter;
  int move_cost, ruleid;
  init_fwd_iter(iter, state);
  while ((ruleid = next_ruleid(iter)) >= 0) {
    state_t *child = new state_t;
    apply_fwd_rule(ruleid, state, child);
    oprint_state(child);
    // move_cost = get_fwd_rule_cost(ruleid);
    successors_list->push_back(make_pair(child, ruleid));
  }
  return successors_list;
}

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

int main(int argc, char const *argv[]) {
  // char const *algorithm = argv[1];
  char const *instance = argv[1];

  // read initial state from stdin
  state_t *initial_state = new state_t;
  read_state(instance, initial_state);
  breadth_first_search(initial_state);

  return 0;
}