cmake_minimum_required(VERSION 3.6)
project(lab3)

include_directories(../../../Загрузки/mpich_4.0.2-2_amd64.deb)
set(CMAKE_CXX_COMPILER "/usr/bin/mpic++")

set(CMAKE_CXX_STANDARD 17)
add_executable(lab3 lab3.cpp)