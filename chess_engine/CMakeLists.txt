cmake_minimum_required(VERSION 4.1)
project(chess_engine)

set(CMAKE_CXX_STANDARD 23)

add_executable(chess_engine src/main.cpp
        src/main.cpp
        include/engine.h
        src/board.cpp
        src/moves.cpp
        src/helpers.cpp
        src/minmax.cpp)
target_include_directories(chess_engine PRIVATE ${CMAKE_SOURCE_DIR}/include)
