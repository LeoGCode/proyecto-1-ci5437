cmake_minimum_required(VERSION 3.25)
project(proyec1AI1)

set(CMAKE_CXX_STANDARD 17)

add_executable( proyec1AI1 
  main.cpp
  src/problems/n-puzzle/15-puzzle/15-puzzle.c 
  src/BFS/BFS.cpp 
  src/BFS/BFS.hpp
  src/utils/psvn.cpp 
  src/utils/psvn.hpp
  src/problems/n-puzzle/15-puzzle/15-puzzle.cpp
  )

