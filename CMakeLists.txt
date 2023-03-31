cmake_minimum_required(VERSION 3.21)
project(texas_holdem_in_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Card)
add_subdirectory(chip)
add_subdirectory(Game)
add_subdirectory(Player)

add_executable(texas main.cpp)
target_link_libraries(texas PUBLIC 
        Card
        chip
        Game
        Player)