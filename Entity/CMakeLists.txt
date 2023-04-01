add_subdirectory(Card)
add_subdirectory(Chip)

add_library(Entity INTERFACE)
target_link_libraries(Entity INTERFACE Card Chip)