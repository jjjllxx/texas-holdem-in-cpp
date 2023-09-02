cmake_minimum_required(VERSION 3.21)
project(TH)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET texas)

include(Algorithms/CMakeLists.txt)
include(Entity/CMakeLists.txt)
include(Game/CMakeLists.txt)
include(GUI/CMakeLists.txt)
include(Player/CMakeLists.txt)

set(SOURCES
    ${TH_CORE_CPPS}
    ${TH_GUI_FILES}
    main.cpp
)

set(LIBS
    Qt::Core
    Qt::Widgets
    Qt::Gui)

add_executable(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt6_INCLUDE_DIRS}
)

target_link_libraries(${TARGET} ${LIBS})

set_target_properties(${TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

if (TH_TEST)
    add_subdirectory("Test")
endif()

# To enable ui_*.h file of Qt
set_property(TARGET texas PROPERTY AUTOMOC ON)
set_property(TARGET texas PROPERTY AUTOUIC ON)