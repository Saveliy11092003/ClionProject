cmake_minimum_required(VERSION 3.16.3)
project(lab7_blas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_CXX_STANDARD 17)

add_executable(lab7_blas Blas.cpp)

### FOR EVM_SERVER: ####
find_package(MKL CONFIG)
if (${MKL_FOUND})
    message(STATUS "found BLAS")

    target_include_directories(lab7_blas PUBLIC $<TARGET_PROPERTY:MKL::MKL,INTERFACE_INCLUDE_DIRECTORIES>)
    target_link_libraries(lab7_blas PUBLIC $<LINK_ONLY:MKL::MKL>)
endif()