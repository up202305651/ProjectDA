cmake_minimum_required(VERSION 3.30)
project(da)

set(CMAKE_CXX_STANDARD 20)

add_executable(da main.cpp
        graph.cpp
        dijkstra.cpp
        main.cpp
        batch.cpp
)
