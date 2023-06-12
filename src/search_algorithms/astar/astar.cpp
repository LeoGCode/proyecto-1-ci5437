#define WHITE 0
#define GRAY 1
#define BLACK 2

#include "astar.hpp"

#include <limits.h>

#include <iostream>
#include <queue>
#include <unordered_map>

#define INFINITY UINT_MAX

using namespace std;

Node *astar_search(state_t *initial_state, heuristic_t heuristic,
                   atomic<int> *num_generated_states,
                   atomic<int> *num_expanded_states) {
  unordered_map<string, int> cost_so_far;  // visited,
  priority_queue<pair<int, Node *>> q;
  // set_color(initial_state, GRAY, visited);
  set_distance(initial_state, 0, cost_so_far);
  Node *root = make_root_node(initial_state);
  q.push(make_pair(heuristic(initial_state), root));
  while (!q.empty()) {
    Node *n = q.top().second;
    q.pop();
    state_t *ns = n->state;
    if (n->g < get_distance(ns, cost_so_far)) {
      set_distance(ns, n->g, cost_so_far);
      if (isGoal(ns)) {
        return n;
      }
      vector<pair<state_t *, Action>> *successors_list = successors(ns);
      num_expanded_states->fetch_add(1);
      for (auto successor : *successors_list) {
        if (heuristic(successor.first) < INFINITY) {
          // set_color(successor.first, GRAY, visited);
          Node *child = make_node(n, successor.first, successor.second);
          q.push(make_pair(child->g + getFwdRuleCost(successor.second) +
                               heuristic(child->state),
                           child));
          num_generated_states->fetch_add(1);
        }
      }
      // set_color(ns, BLACK, visited);
    }
  }
  return nullptr;  // no solution found
}
