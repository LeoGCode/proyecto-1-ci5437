#include "heuristic.hpp"

#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void print_cwd() {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL)
    fprintf(stdout, "Current working dir: %s\n", cwd);
  else
    perror("getcwd() error");
}

abstraction_t* abst;
state_map_t* pdb;

unsigned heuristic(state_t state, std::vector<std::string> pdbs, int additive) {
  int pdb_value = -1;

  for (long unsigned int i = 0; i < pdbs.size(); i++) {
    // Compute PDB Value
    state_t abst_state;
    abstractState(abst, &state, &abst_state);
    const int* a = stateMapGet(pdb, &abst_state);
    // assert(pdb_value != 0);
    int value = *a;
    if (additive)
      pdb_value += value;
    else
      pdb_value = std::max(pdb_value, value);
  }
  return pdb_value;
}

void load_pdb(vector<string> pdb_files) {
  for (long unsigned int i = 0; i < pdb_files.size(); i++) {
    char pdb_fname[1024], abst_fname[1024];
    strcpy(pdb_fname, pdb_files[i].c_str());
    strcat(pdb_fname, ".pdb");
    strcpy(abst_fname, pdb_files[i].c_str());
    strcat(abst_fname, ".abst");
    abst = readAbstractionFromFile(abst_fname);
    FILE* pdb_file = fopen(pdb_fname, "r");
    assert(pdb_file != NULL);
    pdb = readStateMap(pdb_file);
    fclose(pdb_file);
  }
}

unsigned hannoi412(state_t* state) {
  std::vector<std::string> pdbs;
  pdbs = {
      "src/abstractions/hanoi/4-12/hanoi4-12_group_1",
      "src/abstractions/hanoi/4-12/hanoi4-12_group_2",
  };
  return heuristic(*state, pdbs, 0);
}

unsigned hannoi414(state_t* state) {
  std::vector<std::string> pdbs;
  pdbs = {
      "src/abstractions/hanoi/4-14/hanoi4-14_group_1",
      "src/abstractions/hanoi/4-14/hanoi4-14_group_2",
  };
  return heuristic(*state, pdbs, 0);
}

unsigned hannoi418(state_t* state) {
  std::vector<std::string> pdbs;
  pdbs = {
      "src/abstractions/hanoi/4-18/hanoi4-18_group_1",
      "src/abstractions/hanoi/4-18/hanoi4-18_group_2",
  };
  return heuristic(*state, pdbs, 0);
}

unsigned puzzle15(state_t* state) {
  std::vector<std::string> pdbs;
  pdbs = {
      "src/abstractions/n-puzzle/15-puzzle/15-puzzle_group_1",
      "src/abstractions/n-puzzle/15-puzzle/15-puzzle_group_2",
      "src/abstractions/n-puzzle/15-puzzle/15-puzzle_group_3",
  };
  return heuristic(*state, pdbs, 1);
}

unsigned puzzle24(state_t* state) {
  std::vector<std::string> pdbs;
  pdbs = {
      "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_1",
      "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_2",
      "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_3",
      "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_4",
  };
  return heuristic(*state, pdbs, 1);
}

unsigned rubik(state_t* state) {
  std::vector<std::string> pdbs;
  pdbs = {
      "src/abstractions/rubik/3x3/rubik_corner_1",
      "src/abstractions/rubik/3x3/rubik_corner_2",
      "src/abstractions/rubik/3x3/rubik_corner_3",
      "src/abstractions/rubik/3x3/rubik_corner_4",
      "src/abstractions/rubik/3x3/rubik_edge_1",
      "src/abstractions/rubik/3x3/rubik_edge_2",
      "src/abstractions/rubik/3x3/rubik_edge_3",
      "src/abstractions/rubik/3x3/rubik_edge_4",
  };
  return heuristic(*state, pdbs, 1);
}

unsigned topSpin124(state_t* state) {
  std::vector<std::string> pdbs;
  pdbs = {
      "src/abstractions/topSpin/12-4/topspin_12_4_group_1",
      "src/abstractions/topSpin/12-4/topspin_12_4_group_2",
  };
  return heuristic(*state, pdbs, 0);
}

unsigned topSpin144(state_t* state) {
  std::vector<std::string> pdbs;
  pdbs = {
      "src/abstractions/topSpin/14-4/topspin_14_4_group_1",
      "src/abstractions/topSpin/14-4/topspin_14_4_group_2",
  };
  return heuristic(*state, pdbs, 0);
}

unsigned topSpin174(state_t* state) {
  std::vector<std::string> pdbs;
  pdbs = {
      "src/abstractions/topSpin/17-4/topspin_17_4_group_1",
      "src/abstractions/topSpin/17-4/topspin_17_4_group_2",
      "src/abstractions/topSpin/17-4/topspin_17_4_group_3",
  };
  return heuristic(*state, pdbs, 0);
}

heuristic_t getHeuristic(std::string problem) {
  unordered_map<string, vector<string>> pdbs;

  heuristic_t h = NULL;
  pdbs["hanoi4-12"] = {
      "src/abstractions/hanoi/4-12/hanoi4-12_group_1",
      "src/abstractions/hanoi/4-12/hanoi4-12_group_2",
  };
  pdbs["hanoi4-14"] = {
      "src/abstractions/hanoi/4-14/hanoi4-14_group_1",
      "src/abstractions/hanoi/4-14/hanoi4-14_group_2",
  };
  pdbs["hanoi4-18"] = {
      "src/abstractions/hanoi/4-18/hanoi4-18_group_1",
      "src/abstractions/hanoi/4-18/hanoi4-18_group_2",
  };
  pdbs["15-puzzle"] = {
      "src/abstractions/n-puzzle/15-puzzle/15-puzzle_group_1",
      "src/abstractions/n-puzzle/15-puzzle/15-puzzle_group_2",
      "src/abstractions/n-puzzle/15-puzzle/15-puzzle_group_3",
  };
  pdbs["24-puzzle"] = {
      "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_1",
      "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_2",
      "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_3",
      "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_4",
  };
  pdbs["rubik3"] = {
      "src/abstractions/rubik/3x3/rubik_corner_1",
      "src/abstractions/rubik/3x3/rubik_corner_2",
      "src/abstractions/rubik/3x3/rubik_corner_3",
      "src/abstractions/rubik/3x3/rubik_corner_4",
      "src/abstractions/rubik/3x3/rubik_edge_1",
      "src/abstractions/rubik/3x3/rubik_edge_2",
      "src/abstractions/rubik/3x3/rubik_edge_3",
      "src/abstractions/rubik/3x3/rubik_edge_4",
  };
  pdbs["topspin_12_4"] = {
      "src/abstractions/topSpin/12-4/topspin_12_4_group_1",
      "src/abstractions/topSpin/12-4/topspin_12_4_group_2",
  };
  pdbs["topspin_14_4"] = {
      "src/abstractions/topSpin/14-4/topspin_14_4_group_1",
      "src/abstractions/topSpin/14-4/topspin_14_4_group_2",
  };
  pdbs["topspin_17_4"] = {
      "src/abstractions/topSpin/17-4/topspin_17_4_group_1",
      "src/abstractions/topSpin/17-4/topspin_17_4_group_2",
      "src/abstractions/topSpin/17-4/topspin_17_4_group_3",
  };

  if (problem.compare("hanoi4-12") == 0) {
    load_pdb(pdbs["hanoi4-12"]);
    h = &hannoi412;
  } else if (problem.compare("hanoi4-14") == 0) {
    load_pdb(pdbs["hanoi4-14"]);
    h = &hannoi414;
  } else if (problem.compare("hanoi4-18") == 0) {
    load_pdb(pdbs["hanoi4-18"]);
    h = &hannoi418;
  } else if (problem.compare("15-puzzle") == 0) {
    load_pdb(pdbs["15-puzzle"]);
    h = &puzzle15;
  } else if (problem.compare("24-puzzle") == 0) {
    load_pdb(pdbs["24-puzzle"]);
    h = &puzzle24;
  } else if (problem.compare("rubik3") == 0) {
    load_pdb(pdbs["rubik3"]);
    h = &rubik;
  } else if (problem.compare("topspin_12_4") == 0) {
    load_pdb(pdbs["topspin_12_4"]);
    h = &topSpin124;
  } else if (problem.compare("topspin_14_4") == 0) {
    load_pdb(pdbs["topspin_14_4"]);
    h = &topSpin144;
  } else if (problem.compare("topspin_17_4") == 0) {
    load_pdb(pdbs["topspin_17_4"]);
    h = &topSpin174;
  }

  return h;
}