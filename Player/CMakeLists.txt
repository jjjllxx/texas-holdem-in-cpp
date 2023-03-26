add_library(Player STATIC 
    AutoPlayer.cpp
    BasePlayer.cpp
    HumanPlayer.cpp)
target_include_directories(Player PUBLIC "./")