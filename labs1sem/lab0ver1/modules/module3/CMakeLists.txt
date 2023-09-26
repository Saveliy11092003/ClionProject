cmake_minimum_required(VERSION 3.23)
project(module3)

set(CMAKE_CXX_STANDARD 17)

add_library(module3_l STATIC module3.h module3.cpp)