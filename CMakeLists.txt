cmake_minimum_required(VERSION 3.30)
project(DA)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        graph.cpp
        graph.h
        batch.cpp
        batch.h
        dijkstra.cpp
        dijkstra.h
        dijkstra-restricted.cpp
        dijkstra-restricted.h
        dijkstra-sustainable.cpp
        dijkstra-sustainable.h)
