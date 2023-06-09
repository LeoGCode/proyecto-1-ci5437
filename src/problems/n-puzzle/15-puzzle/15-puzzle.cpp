
#include <iostream>

//#include "../../src/utils/psvn.h"
#include "./15-puzzle.c"

void initFwdIter(ruleid_iterator_t *iter, state_t *state) {
    init_fwd_iter(iter, state);
    // cout << "initFwdIter" << endl;
}

int nextRuleid(ruleid_iterator_t *iter) {
    return next_ruleid(iter);
    // cout << "nextRuleid" << endl;
    // return 0;
}
void applyFwdRule(int ruleid, const state_t *state, state_t *child) {
    apply_fwd_rule(ruleid, state, child);
    // cout << "applyFwdRule" << endl;
}
int getFwdRuleCost(int ruleid) {
    return get_fwd_rule_cost(ruleid);
    // cout << "getFwdRuleCost" << endl;
    // return 0;
}
int isGoal(state_t *state) {
    return is_goal(state);
    // cout << "isGoal" << endl;
    // return 0;
}
ssize_t sprintState(char *string, const size_t max_len,
                    const state_t *state_ptr) {
    return sprint_state(string, max_len, state_ptr);
    // cout << "sprintState" << endl;
    // return 0;
}
ssize_t readState(const char *string, state_t *state_ptr) {
    return read_state(string, state_ptr);
    // cout << "readState" << endl;
    // return 0;
}