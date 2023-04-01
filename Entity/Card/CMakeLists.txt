add_library(Card STATIC 
    CardDeck.cpp
    PokerCard.cpp)
target_include_directories(Card PUBLIC "./")