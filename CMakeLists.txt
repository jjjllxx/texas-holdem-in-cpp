cmake_minimum_required(VERSION 3.21)
project(TH)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TH_TARGET texas)
set(TH_SOURCES
    main.cpp
)

include(Algorithms/CMakeLists.txt)
include(Entity/CMakeLists.txt)
include(Game/CMakeLists.txt)
include(Player/CMakeLists.txt)

add_executable(${TH_TARGET} ${TH_SOURCES})
target_include_directories(${TH_TARGET} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(${NP_TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")