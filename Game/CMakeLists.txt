add_library(Game STATIC 
    GameProcess.cpp
    GameTable.cpp)
target_include_directories(Game PUBLIC "./")