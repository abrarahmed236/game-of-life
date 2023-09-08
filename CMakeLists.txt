cmake_minimum_required(VERSION 3.14)

project(game_of_life)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    Game_Of_Life
    src/main.cpp
    src/game_of_life.cpp
)

set_target_properties(Game_Of_Life PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
