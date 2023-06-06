#include <cstring>
#include <iostream>

#include "src/BFS/BFS.h++"
#include "src/utils/psvn.h++"

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

  // read initial state from stdin
  state_t *initial_state;
  read_state(instance, initial_state);

  if (strcmp(algorithm, "bfs") == 0) {
    breadth_first_search(initial_state);
  } else {
    cout << "Algorithm not implemented." << endl;
    cout << "Please, use -h or --help for more information." << endl;
  }

  return 0;
}