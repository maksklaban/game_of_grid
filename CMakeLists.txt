cmake_minimum_required(VERSION 2.8)

project(game_of_grid)

include_directories(src)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_EXE_LINKER_FLAGS "-pthread")

set (SOURCE_EXE main.cpp)

add_executable(main ${SOURCE_EXE})

add_subdirectory(src)

target_link_libraries(main game)