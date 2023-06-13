
#include "manhattan.hpp"

#include <cmath>

unsigned manhattan(state_t *state) {
   unsigned sum = 0;
  for (int i = 0; i < NUMVARS; i++) {
    if (state->vars[i] == 0) continue;
    int grid_size = int(sqrt(NUMVARS));
    int x = i % grid_size;
    int y = i / grid_size;
    int x_goal = state->vars[i] % grid_size;
    int y_goal = state->vars[i] / grid_size;
    sum += abs(x - x_goal) + abs(y - y_goal);
  }
  return sum;
}