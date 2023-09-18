find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

set(TARGET texas_gui)

list(APPEND TH_GUI_FILES
${CMAKE_CURRENT_LIST_DIR}/GUIMainWindow.cpp
)

set(SOURCES
    ${TH_GUI_FILES}
    main.cpp
)

list(APPEND LIBS
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
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# To enable ui_*.h file of Qt
set_property(TARGET texas_gui PROPERTY AUTOMOC ON)
set_property(TARGET texas_gui PROPERTY AUTOUIC ON)