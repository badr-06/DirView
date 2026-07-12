cmake_minimum_required(VERSION 3.16)
project(dirview LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

set(CMAKE_AUTOMOC ON)

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/FileSystemModel.cpp
    src/SortFilterProxyModel.cpp
)

set(HEADERS
    src/MainWindow.h
    src/FileSystemModel.h
    src/SortFilterProxyModel.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)

