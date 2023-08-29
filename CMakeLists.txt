cmake_minimum_required(VERSION 3.21)
project(TH)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET texas)

include(Algorithms/CMakeLists.txt)
include(Entity/CMakeLists.txt)
include(Game/CMakeLists.txt)
include(Player/CMakeLists.txt)

set(SOURCES
    ${TH_CORE_CPPS}
    main.cpp
)

add_executable(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(${TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_subdirectory("Test")