cmake_minimum_required(VERSION 3.21)
project(texas_holdem_in_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")

set(TARGET THCore)

include(texas-holdem-in-cpp/Card/CMakeLists.txt)


set(SOURCES
    ${TH_CORE_CPPS}
)

set(TARGET TH)

set(SOURCES
    main.cpp
)