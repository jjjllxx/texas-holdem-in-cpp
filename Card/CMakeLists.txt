add_library(Card STATIC 
    CardComparison.cpp
    CardDeck.cpp
    CardSelector.cpp
    CardType.cpp
    PokerCard.cpp)
target_include_directories(Card PUBLIC "./")