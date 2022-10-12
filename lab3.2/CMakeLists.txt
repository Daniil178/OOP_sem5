cmake_minimum_required(VERSION 3.16)
project(lab3.2)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)
include_directories(test)

add_library(lib_circuitboard lib/circuitboard.cpp)

add_executable(lab3.2 main.cpp)
target_link_libraries(lab3.2 lib_circuitboard)