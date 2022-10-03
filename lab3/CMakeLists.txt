cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib)
include_directories(test)

add_library(lib_circuitboard lib/circuitboard.cpp)

add_executable(lab3 main.cpp)
target_link_libraries(lab3 lib_circuitboard)