# CMakeList.txt : CMake project for FinalProject1, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

project ("FinalProject1")

# Add source to this project's executable.
add_executable (FinalProject1 "FinalProject.cpp"  "Game.cpp" "GameManager.cpp" "Card.cpp" "Game.h" "GameManager.h" "Card.h" )

# TODO: Add tests and install targets if needed.

target_include_directories(FinalProject1 PUBLIC "./SFML-2.5.1/include" )
target_link_directories(FinalProject1 PUBLIC "./SFML-2.5.1/lib")

target_link_libraries(FinalProject1 PUBLIC "sfml-system-d" "sfml-audio-d" "sfml-window-d" "sfml-graphics-d")