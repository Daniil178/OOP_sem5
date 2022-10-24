cmake_minimum_required(VERSION 3.16)
project(lab3.3)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)
include_directories(test)
include_directories(application)

add_library(lib_pcb lib/pcb.cpp)

add_executable(lab3.3 application/main.cpp application/func.cpp)
target_link_libraries(lab3.3 lib_pcb)