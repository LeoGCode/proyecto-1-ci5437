cmake_minimum_required(VERSION 3.25)
project(proyec1AI1)

set(CMAKE_CXX_STANDARD 17 -pthread -O3)

add_executable( proyec1AI1
        main.cpp
        src/problems/n-puzzle/15-puzzle/15-puzzle.c
        src/search_algorithms/BFS/BFS.cpp
        src/search_algorithms/BFS/BFS.hpp
        src/search_algorithms/DFS/DFS.cpp
        src/search_algorithms/DFS/DFS.hpp
        src/search_algorithms/IDDFS/IDDFS.cpp
        src/search_algorithms/IDDFS/IDDFS.hpp
        src/utils/psvn.cpp
        src/utils/psvn.hpp
        src/problems/n-puzzle/15-puzzle/15-puzzle.cpp
        src/search_algorithms/astar/astar.cpp 
        src/search_algorithms/idastar/idastar.cpp 
        src/problems/n-puzzle/heuristics/manhattan.cpp
        )

