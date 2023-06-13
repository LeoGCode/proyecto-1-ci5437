// this file if for copying, no itent to compile
void initFwdIter(ruleid_iterator_t *iter, state_t *state) {
  init_fwd_iter(iter, state);
}

int nextRuleid(ruleid_iterator_t *iter) { return next_ruleid(iter); }
void applyFwdRule(int ruleid, const state_t *state, state_t *child) {
  apply_fwd_rule(ruleid, state, child);
}
int getFwdRuleCost(int ruleid) { return get_fwd_rule_cost(ruleid); }
int isGoal(state_t *state) { return is_goal(state); }
ssize_t sprintState(char *string, const size_t max_len,
                    const state_t *state_ptr) {
  return sprint_state(string, max_len, state_ptr);
}
ssize_t readState(const char *string, state_t *state_ptr) {
  return read_state(string, state_ptr);
}

int initHistory() { return init_history; }
int fwdRuleValidForHistory(int history, int ruleid) {
  return fwd_rule_valid_for_history(history, ruleid);
}
int nextFwdHistory(int history, int ruleid) {
  return next_fwd_history(history, ruleid);
}

abstraction_t *readAbstractionFromFile(const char *filename) {
  return read_abstraction_from_file(filename);
}

state_map_t *readStateMap(FILE *file) { return read_state_map(file); }

void abstractState(const abstraction_t *abst, const state_t *state,
                   state_t *abst_state) {
  abstract_state(abst, state, abst_state);
}

int *stateMapGet(const state_map_t *map, const state_t *state) {
  return state_map_get(map, state);
}