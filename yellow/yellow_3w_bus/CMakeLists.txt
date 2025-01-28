cmake_minimum_required(VERSION 3.20)
project(yellow_3w_bus)

set(CMAKE_CXX_STANDARD 11)


add_executable(yellow_3w_bus main.cpp bus_manager.cpp query.cpp responses.cpp)
