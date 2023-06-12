
#ifndef PSVN_H
#define PSVN_H

#include <stdbool.h>
#include <sys/types.h>

#include <vector>

using namespace std;

#define NUMVARS 56

typedef int8_t var_t;
typedef struct {
  var_t vars[NUMVARS];
} state_t;

typedef int (*funcptr)(const state_t *, void *);

typedef struct {
  const state_t *my_state;
  funcptr my_funcptr;
} ruleid_iterator_t;

// void init_fwd_iter(ruleid_iterator_t *iter, state_t *state);
// int next_ruleid(ruleid_iterator_t *iter);
// void apply_fwd_rule(int ruleid, const state_t *state, state_t *child);
// int get_fwd_rule_cost(int ruleid);
// int is_goal(state_t *state);
// static ssize_t sprint_state(char *string, const size_t max_len,
//                             const state_t *state_ptr);
// ssize_t read_state(const char *string, state_t *state_ptr);

void initFwdIter(ruleid_iterator_t *iter, state_t *state);
int nextRuleid(ruleid_iterator_t *iter);
void applyFwdRule(int ruleid, const state_t *state, state_t *child);
int getFwdRuleCost(int ruleid);
int isGoal(state_t *state);
static ssize_t sprintState(char *string, const size_t max_len,
                           const state_t *state_ptr);
ssize_t readState(const char *string, state_t *state_ptr);

int initHistory();
int fwdRuleValidForHistory(int history, int ruleid);
int nextFwdHistory(int history, int ruleid);

typedef int Action;

// state_t *init();

typedef struct Node {
  state_t *state;
  struct Node *parent;
  Action action;  // ruleid
  unsigned g;     // cost of partial path
} Node;

Node *make_root_node(state_t *state);
Node *make_node(Node *parent, state_t *state, Action action);
vector<pair<state_t *, Action>> *successors(state_t *state);

void oprint_state(state_t *state);

#endif  // PSVN_H
