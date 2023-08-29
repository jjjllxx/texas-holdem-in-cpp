find_package(GTest REQUIRED)

set(TARGET texas_test)
set(SOURCES
    ${TH_CORE_CPPS}
    ${TH_TEST_CPPS}
    main.cpp
)

include(${PROJECT_SOURCE_DIR}/Algorithms/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Entity/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Game/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Player/CMakeLists.txt)

add_executable(${TARGET}
     ${SOURCES})

target_link_libraries(${TARGET} PRIVATE
    GTest::gtest)

target_include_directories(${TARGET} PRIVATE 
    ${PROJECT_SOURCE_DIR}
)

set_target_properties(${TARGET} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)