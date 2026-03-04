cmake_minimum_required(VERSION 3.16)
project(Chess-application VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.9.1/mingw_64/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    MainWindow.cpp
    MainWindow.h
    StartScreen.cpp
    StartScreen.h
    GameScreen.cpp
    GameScreen.h
)

add_executable(Chess-application ${PROJECT_SOURCES})

target_link_libraries(Chess-application PRIVATE Qt6::Widgets)