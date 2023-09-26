cmake_minimum_required(VERSION 3.23)
project(module2)

set(CMAKE_CXX_STANDARD 17)


add_library(module2_l STATIC module2.h module2.cpp)