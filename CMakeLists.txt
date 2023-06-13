cmake_minimum_required(VERSION 3.25)
project(hanoi4-14_h1)

set(CMAKE_CXX_STANDARD 17 -pthread -g)

add_executable( hanoi4-14_h1
        main.cpp
        src/problems/hanoi/hanoi4-14/hanoi4-14_h1.c
        src/search_algorithms/BFS/BFS.cpp
        src/search_algorithms/BFS/BFS.hpp
        src/search_algorithms/DFS/DFS.cpp
        src/search_algorithms/DFS/DFS.hpp
        src/search_algorithms/IDDFS/IDDFS.cpp
        src/search_algorithms/IDDFS/IDDFS.hpp
        src/utils/psvn.cpp
        src/utils/psvn.hpp
        src/problems/hanoi/hanoi4-14/hanoi4-14_h1.cpp
        src/search_algorithms/astar/astar.cpp 
        src/search_algorithms/idastar/idastar.cpp
        src/problems/n-puzzle/heuristics/manhattan.cpp
        src/utils/heuristic.cpp
        
  )

