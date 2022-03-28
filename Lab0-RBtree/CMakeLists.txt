cmake_minimum_required(VERSION 3.15)
project(RBtree)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(compilado
    src/main.cpp src/rbtree.h src/rbtree.cpp
)
