cmake_minimum_required(VERSION 3.21)
project(MultiSort)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,4000000")

add_executable(MultiSort main.cpp)

