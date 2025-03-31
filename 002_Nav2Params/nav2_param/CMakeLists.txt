cmake_minimum_required(VERSION 3.5)

project(nav2_param VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(yaml-cpp REQUIRED)

#---------------- အင်ကလု ----------------#
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rom_robot/header)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rom_robot/source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(CMAKE_AUTOUIC_SEARCH_PATHS src)

#set(UI_FILES src/nav2_window.ui)
#qt5_wrap_ui(UI_HEADERS ${UI_FILES})

#set(PROJECT_SOURCES ${UI_HEADERS})

add_executable(Nav2ParamEditor
    src/main.cpp
    src/nav2_window.cpp
    src/nav2_window.h
    src/yaml_handler.h
    src/yaml_handler.cpp
    #${UI_HEADERS}
)
target_link_libraries(Nav2ParamEditor ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} yaml-cpp)

