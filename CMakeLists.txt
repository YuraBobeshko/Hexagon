cmake_minimum_required(VERSION 3.22)
project(Hexagon)
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
add_executable(Hexagon Hexagon.cpp Game.cpp Field.cpp Player.cpp Board.cpp Font.cpp)
target_compile_definitions(Hexagon PRIVATE SFML_STATIC)    # SFML related
target_link_libraries(Hexagon sfml-graphics sfml-audio sfml-network sfml-window sfml-system) # SFML related
