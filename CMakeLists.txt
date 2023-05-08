cmake_minimum_required(VERSION 3.25)
project(Hexxagon)

set(CMAKE_CXX_STANDARD 14)

include_directories(Hexxagon)

add_executable(Hexxagon
        Hexxagon/Game.cpp
        Hexxagon/Game.h
        Hexxagon/Hexxagon.cpp Hexxagon/Field.cpp)

set(SFML_DIR "C:\\Users\\paul\\CLionProjects\\lib\\sfml\\GCC 7.3.0 MinGW (SEH) - 64-bit\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(Hexxagon sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)