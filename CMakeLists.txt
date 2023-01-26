cmake_minimum_required(VERSION 3.21)
project(texas_holdem_in_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(Card)

add_executable(texas_holdem_in_cpp
        Card/CardComparison.cpp
        Card/CardDeck.cpp
        Card/CardSelector.cpp
        Card/CardType.cpp
        Card/PokerCard.cpp
        main.cpp)