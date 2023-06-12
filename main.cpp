#include <sys/resource.h>

#include <atomic>
#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

#include "src/search_algorithms/BFS/BFS.hpp"
#include "src/search_algorithms/DFS/DFS.hpp"
#include "src/search_algorithms/IDDFS/IDDFS.hpp"
#include "src/search_algorithms/astar/astar.hpp"
#include "src/search_algorithms/idastar/idastar.hpp"
// #include "src/utils/psvn.hpp"

#include "src/problems/n-puzzle/heuristics/manhattan.hpp"

void print_help(char *argv0) {
  cout << "Usage: " << argv0 << " <algorithm> <instance> <timeout> [heuristic]"
       << endl;
  cout << "  <algorithm> = {bfs, dfs, iddfs, astar, idastar}" << endl;
  cout << "  <instance> = vector of length corresponding to the problem"
       << endl;
  cout << "  <timeout> = timeout in seconds" << endl;
  cout << "  [heuristic] = {manhattan} (required for astar and idastar)"
       << endl;
  cout << "  the heuristic must match the problem" << endl;
}

void print_short_help(char *argv0) {
  cout << "Usage: " << argv0 << " <algorithm> <instance> <timeout> [heuristic]"
       << endl;
  cout << "Please, use -h or --help for more information." << endl;
}

atomic<int> num_generated_states;
atomic<int> num_expanded_states;
// flag to indicate if main program has finished
atomic<bool> main_finished(false);
// flag to indicate if timeout has been reached
atomic<bool> timeout_reached(false);

heuristic_t check_heuristic(int argc, char *argv[], char const *heuristic) {
  if (argc != 5) {
    print_short_help(argv[0]);
    return NULL;
  }
  if (strcmp(heuristic, "manhattan") == 0) {
    return manhattan;
  } else {
    cout << "Heuristic not implemented." << endl;
    cout << "Please, use -h or --help for more information." << endl;
    return NULL;
  }
}

int main_program(int argc, char *argv[]) {
  if (argc > 1 &&
      (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
    print_help(argv[0]);
    return 0;
  }
  if (argc < 4) {
    print_short_help(argv[0]);
    return 0;
  }
  char const *algorithm = argv[1];
  char const *instance = argv[2];

  // read initial state from stdin
  state_t *initial_state = (state_t *)malloc(sizeof(state_t));
  readState(instance, initial_state);
  // oprint_state(initial_state);

  if (strcmp(algorithm, "bfs") == 0) {
    breadth_first_search(initial_state, &num_generated_states,
                         &num_expanded_states);
  } else if (strcmp(algorithm, "dfs") == 0) {
    depth_first_search(initial_state, &num_generated_states,
                       &num_expanded_states);
  } else if (strcmp(algorithm, "iddfs") == 0) {
    iterative_deepening_depth_first_search(initial_state, &num_generated_states,
                                           &num_expanded_states);
  } else if (strcmp(algorithm, "astar") == 0) {
    heuristic_t heuristic = check_heuristic(argc, argv, argv[4]);
    if (heuristic == NULL) {
      return 0;
    }
    astar_search(initial_state, heuristic, &num_generated_states,
                 &num_expanded_states);
  } else if (strcmp(algorithm, "idastar") == 0) {
    heuristic_t heuristic = check_heuristic(argc, argv, argv[4]);
    if (heuristic == NULL) {
      return 0;
    }
    idastar_search(initial_state, heuristic, &num_generated_states,
                   &num_expanded_states);
  } else {
    cout << "Algorithm not implemented." << endl;
    cout << "Please, use -h or --help for more information." << endl;
  }
  main_finished.store(true);
  return 0;
}

void wait_timeout(int timeout) {
  this_thread::sleep_for(chrono::seconds(timeout));
  cout << "Timeout reached. Killing the program." << endl;
  timeout_reached.store(true);
}

int main(int argc, char *argv[]) {
    main_program(argc, argv);

  // launch the main program in a separate thread
  thread t1(main_program, argc, argv);
  // launch a thread that waits for a timeout
  // we wait 15 minutes before killing the program
  int64_t timeout = stoi(argv[3]);
  // cout << "Timeout set to " << timeout << " seconds." << endl;
  thread t2(wait_timeout, timeout);

  // verify if the main program has finished or
  // the timeout has been reached
  while (!main_finished.load() && !timeout_reached.load()) {
    this_thread::sleep_for(chrono::seconds(1));
  }
  // if the main program has finished, we kill the timeout thread
  if (main_finished.load()) {
    printf("Main program finished.\n");
    t2.detach();
    t1.join();
    // if the timeout has been reached, we kill the main program
  } else if (timeout_reached.load()) {
    printf("Timeout reached.\n");
    t1.detach();
    t2.join();
  }
  cout << "Number of generated states: " << num_generated_states.load() << endl;
  cout << "Number of expanded states: " << num_expanded_states.load() << endl;

  return 0;
}