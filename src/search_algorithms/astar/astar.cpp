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
                   atomic<int> *num_expanded_states, atomic<int> *max_depth) {
  unordered_map<string, unsigned> cost_so_far;  // visited,
  priority_queue<pair<int, Node *>, vector<pair<int, Node *>>,
                 greater<pair<int, Node *>>>
      q;
  // set_color(initial_state, GRAY, visited);
  Node *root = make_root_node(initial_state);
  q.push(make_pair(heuristic(initial_state), root));
  while (!q.empty()) {
    Node *n = q.top().second;
    q.pop();
    state_t *ns = n->state;
    if (n->g < get_distance(ns, cost_so_far)) {
      set_distance(ns, n->g, cost_so_far);
      if (isGoal(ns)) {
        printf("Solution found!\n");
        return n;
      }
      vector<pair<state_t *, Action>> *successors_list = successors(ns);
      if (successors == nullptr) {
        cout << "Out of memory" << endl;
        return nullptr;
      }
      num_expanded_states->fetch_add(1);
      // printf("Expanded: %d\n", num_expanded_states->load());
      for (auto successor : *successors_list) {
        if (heuristic(successor.first) < INFINITY) {
          // set_color(successor.first, GRAY, visited);
          Node *child = make_node(n, successor.first, successor.second);
          (*max_depth) = max(max_depth->load(), child->depth);
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
