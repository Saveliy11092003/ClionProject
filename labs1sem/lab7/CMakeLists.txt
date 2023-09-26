
cmake_minimum_required(VERSION 3.16.3)
project(lab7)

##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_CXX_STANDARD 17)
add_executable(lab7 lab7ver3.cpp)
find_package(MKL CONFIG)
if (${MKL_FOUND})
    message(STATUS "found BLAS")

    target_include_directories(lab7 PUBLIC $<TARGET_PROPERTY:MKL::MKL,INTERFACE_INCLUDE_DIRECTORIES>)
    target_link_libraries(lab7 PUBLIC $<LINK_ONLY:MKL::MKL>)
endif()

##add_executable(lab7 lab7ver1.cpp)
##add_executable(lab7 lab7ver2.cpp)
