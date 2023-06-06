
#ifndef PSVN_H
#define PSVN_H

#include <stdbool.h>
#include <sys/types.h>

#include <vector>

using namespace std;

typedef struct {
} state_t;
typedef struct {
} ruleid_iterator_t;
void init_fwd_iter(ruleid_iterator_t *iter, state_t *state);
int next_ruleid(ruleid_iterator_t *iter);
void apply_fwd_rule(int ruleid, const state_t *state, state_t *child);
int get_fwd_rule_cost(int ruleid);
int is_goal(state_t *state);

static ssize_t sprint_state(char *string, const size_t max_len,
                            const state_t *state_ptr);
ssize_t read_state(const char *string, state_t *state_ptr);

typedef int Action;

state_t *init();

typedef struct Node {
  state_t *state;
  struct Node *parent;
  Action action;  // ruleid
  unsigned g;     // cost of partial path
} Node;

Node *make_root_node(state_t *state);
Node *make_node(Node *parent, state_t *state, Action action);
vector<pair<state_t *, Action>> *successors(state_t *state);

#endif  // PSVN_H
