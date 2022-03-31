cmake_minimum_required(VERSION 3.20)
project(Lab1_BplusTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(Lab1_BplusTree src/main.cpp src/BplusTree.cpp src/BplusTree.h)
