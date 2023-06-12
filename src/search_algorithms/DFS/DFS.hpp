#ifndef DFS_HPP
#define DFS_HPP
#include <atomic>

#include "../../utils/psvn.hpp"

Node *depth_first_search(state_t *initial_state,
                         std::atomic<int> *num_generated_states,
                         std::atomic<int> *num_expanded_states);

#endif  // DFS_HPP
