
#ifndef PSVN_H
#define PSVN_H

#include <stdbool.h>
#include <sys/types.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#define NUMVARS 56
#define NUMDOMAINS 1

typedef int8_t var_t;
typedef struct {
  var_t vars[NUMVARS];
} state_t;

typedef int (*funcptr)(const state_t *, void *);

typedef struct {
  const state_t *my_state;
  funcptr my_funcptr;
} ruleid_iterator_t;
typedef struct {
  int size;
  var_t *v;
} abst_array_t;

typedef struct {
  var_t *value_map[NUMDOMAINS];
  uint8_t project_away_var[NUMVARS];
  abst_array_t *mapped_in[NUMDOMAINS];
  int *fwd_rule_label_sets;
  int *bwd_rule_label_sets;
} abstraction_t;

typedef struct {
  state_t state;
  int value;
} state_map_entry_t;

typedef struct {
  state_map_entry_t *entries;
  int64_t avail_entries;
  int64_t max_entry;
} state_map_t;

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
int getFwdRuleCost(int ruleid);

ssize_t sprintState(char *string, const size_t max_len,
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

// heuristic function to be used in A* and IDA*
typedef unsigned (*heuristic_t)(state_t *);

// color embedding
// 0 - white
// 1 - gray
// 2 - black
int COLOR(char c);

void set_color(state_t *state, int color, unordered_map<string, int> &visited);
int get_color(state_t *state, unordered_map<string, int> &visited);
void set_distance(state_t *state, unsigned distance,
                  unordered_map<string, unsigned> &cost_so_far);
unsigned get_distance(state_t *state,
                      unordered_map<string, unsigned> &cost_so_far);

abstraction_t *readAbstractionFromFile(const char *filename);

state_map_t *readStateMap(FILE *file);

void abstractState(const abstraction_t *abst, const state_t *state,
                   state_t *abst_state);

int *stateMapGet(const state_map_t *map, const state_t *state);

#endif  // PSVN_H
