cmake_minimum_required(VERSION 3.21)
project(evaluateexpresion_sin_nombre_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(evaluateexpresion_sin_nombre_3
        main.cpp
        solution.h
        tester.h)
