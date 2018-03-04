cmake_minimum_required(VERSION 3.9)
project(SmallSquare)

set(CMAKE_CXX_STANDARD 11)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR})

add_executable(SmallSquare main.cpp)