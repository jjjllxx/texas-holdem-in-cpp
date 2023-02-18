cmake_minimum_required(VERSION 3.21)
project(texas_holdem_in_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(texas_holdem_in_cpp
        Card/CardComparison.cpp 
        Card/CardDeck.cpp
        Card/CardSelector.cpp
        Card/CardType.cpp
        Card/PokerCard.cpp  
        Player/AutoPlayer.cpp
        Player/BasePlayer.cpp
        Player/HumanPlayer.cpp  
        main.cpp)