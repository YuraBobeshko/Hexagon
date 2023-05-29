cmake_minimum_required(VERSION 3.22)
project(Hexxagon)
set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)    # SFML related
# 3 SFML related commands
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)
add_executable(Hexxagon Hexxagon.cpp Game.cpp Field.cpp Player.cpp Board.cpp Font.cpp)
target_compile_definitions(Hexxagon PRIVATE SFML_STATIC)    # SFML related
target_link_libraries(Hexxagon sfml-graphics sfml-audio sfml-network sfml-window sfml-system) # SFML related
