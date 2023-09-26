cmake_minimum_required(VERSION 3.23)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./vector)

add_executable(untitled1 main.cpp)
add_library(vector_t PUBLIC vector.c vector.h)
target_link_libraries(untitled1 PRIVATE vector_lib)
#vector/vector.cpp vector/vector.h