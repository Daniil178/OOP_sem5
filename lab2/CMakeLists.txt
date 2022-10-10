cmake_minimum_required(VERSION 3.16)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)
include_directories(test)

add_library(lib_deltoid lib/deltoid.cpp)

add_executable(lab2 main.cpp)
target_link_libraries(lab2 lib_deltoid)