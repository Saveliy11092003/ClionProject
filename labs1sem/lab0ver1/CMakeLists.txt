cmake_minimum_required(VERSION 3.23)
project(lab0ver1)

add_executable(lab0ver1 main.cpp )

add_subdirectory(modules/module1)
add_subdirectory(modules/module2)
add_subdirectory(modules/module3)


target_include_directories(lab0ver1 PUBLIC modules/module1)
target_include_directories(lab0ver1 PUBLIC modules/module2)
target_include_directories(lab0ver1 PUBLIC modules/module3)


target_link_libraries(lab0ver1 PRIVATE module1_l module2_l module3_l)

