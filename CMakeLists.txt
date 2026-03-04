cmake_minimum_required(VERSION 3.16)
project(Chess-application VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.9.1/mingw_64/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Widgets Svg SvgWidgets)

set(PROJECT_SOURCES
    src/main.cpp

    src/UI/MainWindow.cpp
    src/UI/MainWindow.h

    src/UI/home_screen/StartScreen.cpp
    src/UI/home_screen/StartScreen.h
    src/UI/game_screen/GameScreen.cpp
    src/UI/game_screen/GameScreen.h
)

add_executable(Chess-application ${PROJECT_SOURCES})

target_include_directories(Chess-application PRIVATE
    src
    src/UI
    src/UI/home_screen
    src/UI/game_screen
)

target_link_libraries(Chess-application PRIVATE Qt6::Widgets Qt6::Svg Qt6::SvgWidgets)