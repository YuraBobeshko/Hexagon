cmake_minimum_required(VERSION 3.25)
project(Hexxagon)

set(CMAKE_CXX_STANDARD 14)

include_directories(Hexxagon)

add_executable(Hexxagon
        Hexxagon/Game.cpp
        Hexxagon/Game.h
        Hexxagon/Hexxagon.cpp)
