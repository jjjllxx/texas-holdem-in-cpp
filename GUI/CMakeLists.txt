find_package(Qt6 QUIET COMPONENTS Core Widgets Gui)
find_package(Qt5 QUIET COMPONENTS Core Widgets Gui)

if (Qt6_FOUND)
    message(STATUS "Found Qt 6")
    set(QT_VERSION 6)
    set(QT_INCLUDE_DIRS ${Qt6_INCLUDE_DIRS})
    set(QT_LIBRARIES Qt6::Core Qt6::Widgets Qt6::Gui)
elseif (Qt5_FOUND)
    message(STATUS "Found Qt 5")
    set(QT_VERSION 5)
    set(QT_INCLUDE_DIRS ${Qt5_INCLUDE_DIRS})
    set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::Gui)
else ()
    message(FATAL_ERROR "Qt not found on this system.")
endif ()

set(TARGET texas_gui)
list(APPEND TH_GUI_FILES
    ${CMAKE_CURRENT_LIST_DIR}/GUIMainWindow.cpp
)
set(SOURCES
    ${TH_GUI_FILES}
    main.cpp
)
list(APPEND LIBS
    ${QT_LIBRARIES}
)

add_executable(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${QT_INCLUDE_DIRS}
)
target_link_libraries(${TARGET} ${LIBS})

set_target_properties(${TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# To enable ui_*.h file of Qt
set_property(TARGET texas_gui PROPERTY AUTOMOC ON)
set_property(TARGET texas_gui PROPERTY AUTOUIC ON)