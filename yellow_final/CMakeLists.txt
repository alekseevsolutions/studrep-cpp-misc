cmake_minimum_required(VERSION 3.20)
project(yellow_final)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        test_runner.h
        test_runner.cpp
        main.cpp)

add_executable(yellow_final ${SOURCES})
