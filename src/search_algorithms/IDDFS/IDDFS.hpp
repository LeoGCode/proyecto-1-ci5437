#ifndef IDDFS_HPP
#define IDDFS_HPP
#include <atomic>

#include "../../utils/psvn.hpp"

Node *iterative_deepening_depth_first_search(state_t *initial_state,
                                             atomic<int> *num_generated_states,
                                             atomic<int> *num_expanded_states);

#endif  // IDDFS_HPP
