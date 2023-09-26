cmake_minimum_required(VERSION 3.6)
project(lab5)

include_directories(../../../Загрузки/mpich_4.0.2-2_amd64.deb)
set(CMAKE_CXX_COMPILER "/usr/bin/mpic++")

set(CMAKE_CXX_STANDARD 17)
add_executable(lab5 lab5.cpp)