cmake_minimum_required(VERSION 3.26)
project(shipping-system)

set(CMAKE_CXX_STANDARD 17)

add_executable(shipping-system
        main.cpp
        src/Graph.h
        src/Node.cpp
        src/Algorithms.cpp)
