#ifndef HEURISTIC_H
#define HEURIS

#include <vector>
#include <string>
#include <algorithm>

/*
Return de Heuristic Value for a given state in problem

Problem string posible values:
- hanoi4-12
- hanoi4-14
- hanoi4-15
- 15-puzzle
- 24-puzzle
- rubik
- topSpin12-4
- topSpin14-4
- topSpin17-4

*/
int getHeuristic( state_t state, std::string problem );

#endif