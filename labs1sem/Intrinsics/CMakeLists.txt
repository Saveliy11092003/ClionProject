cmake_minimum_required(VERSION 3.16.3)
project(lab7_intrinsics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

add_executable(lab7_intrinsics Intrinsics.cpp)
