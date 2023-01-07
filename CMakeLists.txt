cmake_minimum_required(VERSION 3.21)
project(texas_holdem_in_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(Card)

add_executable(texas_holdem_in_cpp
        Card/CardDeck.cpp
        Card/CardType.cpp
        Card/HandCard.cpp
        Card/PokerCard.cpp
        main.cpp)