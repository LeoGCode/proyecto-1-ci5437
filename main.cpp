#include <cstring>
#include <iostream>

#include "src/BFS/BFS.hpp"
#include "src/utils/psvn.hpp"

void print_help(char *argv0) {
  cout << "Usage: " << argv0 << " <algorithm> <instance>" << endl;
  cout << "  <algorithm> = {bfs}"
       << endl;  //, dfs, iddfs, astar, idastar}" << endl;
  cout << "  <instance> = vector of length corresponding to the problem"
       << endl;
}

int main(int argc, char *argv[]) {
  if (argc > 1 &&
      (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
    print_help(argv[0]);
    return 0;
  }
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <algorithm> <instance>" << endl;
    cout << "Please, use -h or --help for more information." << endl;
    return 0;
  }
  char const *algorithm = argv[1];
  char const *instance = argv[2];
  //   char const *instance = "7 15 8 2 13 6 3 12 11 B 4 10 9 5 1 14";

  // read initial state from stdin
  state_t *initial_state = new state_t;
  readState(instance, initial_state);
  //   breadth_first_search(initial_state);

  if (strcmp(algorithm, "bfs") == 0) {
    breadth_first_search(initial_state);
  } else {
    cout << "Algorithm not implemented." << endl;
    cout << "Please, use -h or --help for more information." << endl;
  }

  return 0;
}