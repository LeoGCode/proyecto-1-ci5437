#include <vector>
#include <string>
#include <algorithm>
# include "heuristic.hpp"

int heuristic( state_t state, std::vector<std::string> pdbs, int additive ){
    int pdb_value = -1;
    
    for (long unsigned int i = 0; i < pdbs.size(); i++)
    {
        // Get PDB state map and abstract space definition
        char pdb_fname[1024], abst_fname[1024];
        strcpy(pdb_fname, pdbs[i].c_str());
        strcat(pdb_fname, ".pdb");
        strcpy(abst_fname, pdbs[i].c_str());
        strcat(abst_fname, ".abst");
        abstraction_t *abst = read_abstraction_from_file(abst_fname);
        FILE *pdb_file = fopen(pdb_fname, "r");
        assert(pdb_file != NULL);
        state_map_t *pdb = read_state_map(pdb_file);
        fclose(pdb_file);

        // Compute PDB Value
        state_t abst_state;
        abstract_state(abst, &state, &abst_state);
        const int *a = state_map_get(pdb, &abst_state);
        assert(pdb_value != 0);
        int value = *a;
        if (additive)
            pdb_value += value;
        else
            pdb_value = std::max(pdb_value, value);
    }
    return pdb_value;
}

int getHeuristic( state_t state, std::string problem ){

    std::vector<std::string> pdbs;
    if (problem.compare("hanoi4-12") == 0)
    {
        pdbs  = { 
            "src/abstractions/hanoi/4-12/hanoi4-12_group_1",
            "src/abstractions/hanoi/4-12/hanoi4-12_group_2",
        };

        return heuristic( state, pdbs, 1 );
    }
    else if (problem.compare("hanoi4-14") == 0)
    {
        pdbs  = { 
            "src/abstractions/hanoi/4-14/hanoi4-14_group_1",
            "src/abstractions/hanoi/4-14/hanoi4-14_group_2",
        };

        return heuristic( state, pdbs, 1 );
    }
    else if (problem.compare("hanoi4-18") == 0)
    {
        pdbs  = { 
            "src/abstractions/hanoi/4-18/hanoi4-18_group_1",
            "src/abstractions/hanoi/4-18/hanoi4-18_group_2",
        };

        return heuristic( state, pdbs, 1 );
    }
    else if (problem.compare("15-puzzle") == 0)
    {
        pdbs  = { 
            "src/abstractions/n-puzzle/15-puzzle/15-puzzle_group_1",
            "src/abstractions/n-puzzle/15-puzzle/15-puzzle_group_2",
            "src/abstractions/n-puzzle/15-puzzle/15-puzzle_group_3",
        };

        return heuristic( state, pdbs, 0 );
    }
    else if (problem.compare("24-puzzle") == 0)
    {
        pdbs  = { 
            "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_1",
            "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_2",
            "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_3",
            "src/abstractions/n-puzzle/24-puzzle/24-puzzle_group_4",
        };

        return heuristic( state, pdbs, 0 );
    }
    else if (problem.compare("rubik") == 0)
    {
        pdbs  = { 
            "src/abstractions/rubik/3x3/rubik_corner_1",
            "src/abstractions/rubik/3x3/rubik_corner_2",
            "src/abstractions/rubik/3x3/rubik_corner_3",
            "src/abstractions/rubik/3x3/rubik_corner_4",
            "src/abstractions/rubik/3x3/rubik_edge_1",
            "src/abstractions/rubik/3x3/rubik_edge_2",
            "src/abstractions/rubik/3x3/rubik_edge_3",
            "src/abstractions/rubik/3x3/rubik_edge_4",
        };

        return heuristic( state, pdbs, 1 );
    }
    else if (problem.compare("topSpin12-4") == 0)
    {
        pdbs  = { 
            "src/abstractions/topSpin/12-4/topspin_12_4_group_1.txt",
            "src/abstractions/topSpin/12-4/topspin_12_4_group_2.txt",
        };

        return heuristic( state, pdbs, 1 );
    }
    else if (problem.compare("topSpin14-4") == 0)
    {
        pdbs  = { 
            "src/abstractions/topSpin/14-4/topspin_14_4_group_1.txt",
            "src/abstractions/topSpin/14-4/topspin_14_4_group_2.txt",
        };

        return heuristic( state, pdbs, 1 );
    }
    else if (problem.compare("topSpin17-4") == 0)
    {
        pdbs  = { 
            "src/abstractions/topSpin/17-4/topspin_17_4_group_1.txt",
            "src/abstractions/topSpin/17-4/topspin_17_4_group_2.txt",
            "src/abstractions/topSpin/17-4/topspin_17_4_group_3.txt",
        };

        return heuristic( state, pdbs, 1 );
    }
    
    return -1;    
}