cmake_minimum_required(VERSION 3.10)
project(Tutorial)
add_executable(exec main.cpp Tictactoe.cpp)
add_executable(testprogram catch_amalgamated.cpp test.cpp Tictactoe.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
