cmake_minimum_required(VERSION 3.21)
project(DigitalPiano)

set(CMAKE_CXX_STANDARD 14)

add_executable(DigitalPiano main.cpp Piano.cpp Piano.h PianoKey.cpp PianoKey.h)

find_library(WINMM winmm)
target_link_libraries(DigitalPiano WINMM)
