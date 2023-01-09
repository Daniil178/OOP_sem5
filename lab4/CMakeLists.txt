cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(lab4)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(game main.cpp graphics/TileOnMap.cpp)
add_executable(dirt dirt.cpp)

target_link_libraries(game sfml-graphics sfml-audio)
target_link_libraries(dirt sfml-graphics sfml-audio)

include_directories(app application)

add_library(objects application/RPG_Object.cpp application/Game.cpp application/Level.cpp application/Cell.cpp
        application/Item.cpp application/Weapon.cpp application/Ammo_container.cpp application/Medicine_Kit.cpp
        application/Unit.cpp application/Forager.cpp application/Wild.cpp application/Rational.cpp
        application/Operative.cpp application/Table.cpp application/help_func.h)

target_link_libraries(game objects)
target_link_libraries(dirt objects)