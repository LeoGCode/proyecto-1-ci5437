#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <atomic>

#include "../../utils/psvn.hpp"

using namespace std;

Node *astar_search(state_t *initial_state, heuristic_t heuristic,
                   atomic<int> *num_generated_states,
                   atomic<int> *num_expanded_states);

#endif  // ASTAR_HPP