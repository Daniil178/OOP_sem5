cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(lab4)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(game main.cpp)
add_executable(dirt dirt.cpp)

target_link_libraries(game sfml-graphics sfml-audio)