add_library(CardAlgo STATIC 
    CardComparison.cpp
    CardSelector.cpp
    CardType.cpp)
target_include_directories(CardAlgo PUBLIC "./")