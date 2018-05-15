cmake_minimum_required(VERSION 2.8)

project(game_of_grid)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_EXE_LINKER_FLAGS "-pthread")

set (SOURCE_EXE main.cpp)
set (SOURCE_LIB game_of_life.cpp game_grid.cpp)

add_library(game STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main game)