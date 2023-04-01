add_subdirectory(Card)
# add_subdirectory(Random)

add_library(Algo INTERFACE)
target_link_libraries(Algo INTERFACE CardAlgo)