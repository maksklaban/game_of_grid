cmake_minimum_required(VERSION 2.8)

project(game_of_life_lib)

set (SOURCE_LIB game_of_life.cpp game_grid.cpp)

add_library(game STATIC ${SOURCE_LIB})

