#ifndef IDASTAR_HPP
#define IDASTAR_HPP

#include <atomic>

#include "../../utils/psvn.hpp"

Node *idastar_search(state_t *initial_state, heuristic_t heuristic,
                     atomic<int> *num_generated_states,
                     atomic<int> *num_expanded_states);

#endif  // IDASTAR_HPP