#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <atomic>

#include "../../utils/psvn.hpp"

Node *astar_search(state_t *initial_state,
                   std::atomic<int> *num_generated_states,
                   std::atomic<int> *num_expanded_states);

#endif  // ASTAR_HPP