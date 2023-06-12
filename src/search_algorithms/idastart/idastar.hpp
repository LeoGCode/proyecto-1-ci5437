#ifndef IDASTAR_HPP
#define IDASTAR_HPP

#include <atomic>

#include "../../utils/psvn.hpp"

Node *idastar_search(state_t *initial_state,
                     std::atomic<int> *num_generated_states,
                     std::atomic<int> *num_expanded_states);

#endif  // IDASTAR_HPP