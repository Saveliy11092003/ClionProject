cmake_minimum_required(VERSION 3.23)
project(_)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(BIG_INT)

add_executable(vector_example main.cpp)


target_include_directories(_ PRIVATE BIG_INT)
target_link_libraries(_ PRIVATE BIG_INT_l)