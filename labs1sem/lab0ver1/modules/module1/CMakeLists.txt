cmake_minimum_required(VERSION 3.23)
project(module1)

set(CMAKE_CXX_STANDARD 17)

add_library(module1_l STATIC module1.h module1.cpp)