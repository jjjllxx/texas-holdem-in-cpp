cmake_minimum_required(VERSION 3.16)
project(TH)

find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET texas)

include(Algorithms/CMakeLists.txt)
include(Common/CMakeLists.txt)
include(Core/CMakeLists.txt)
include(Entity/CMakeLists.txt)

set(SOURCES
    ${TH_CORE_CPPS}
    main.cpp
)

set(LIBS
    nlohmann_json::nlohmann_json
    spdlog::spdlog)

add_executable(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${TARGET} ${LIBS})

set_target_properties(${TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

if (TH_TEST)
    add_subdirectory("Test")
endif()

if (TH_GUI)
    add_subdirectory("GUI")
endif()