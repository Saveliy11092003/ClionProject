cmake_minimum_required(VERSION 3.22)
project(Lab1_oop)

add_compile_options(-fno-elide-constructors)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1_oop BigInt_Tests.cpp BigInt_directory1/BigInt.cpp BigInt_directory1/BigInt.h My_Tests.cpp)

add_subdirectory(BigInt_directory1)

target_include_directories(Lab1_oop PRIVATE BigInt_directory1)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_link_libraries(Lab1_oop PRIVATE BigInt_t gtest_main)