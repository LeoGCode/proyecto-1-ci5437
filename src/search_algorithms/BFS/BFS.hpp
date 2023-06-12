#ifndef BFS_H
#define BFS_H
#include <atomic>

#include "../../utils/psvn.hpp"

Node *breadth_first_search(state_t *initial_state,
                           std::atomic<int> *num_generated_states,
                           std::atomic<int> *num_expanded_states);
#endif  // BFS_H