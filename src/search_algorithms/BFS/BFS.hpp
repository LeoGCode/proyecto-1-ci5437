#ifndef BFS_H
#define BFS_H
#include <atomic>

#include "../../utils/psvn.hpp"

using namespace std;

Node *breadth_first_search(state_t *initial_state,
                           atomic<int> *num_generated_states,
                           atomic<int> *num_expanded_states,
                           atomic<int> *max_depth);
#endif  // BFS_H