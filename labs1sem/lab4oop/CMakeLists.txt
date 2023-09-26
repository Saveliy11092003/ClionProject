cmake_minimum_required(VERSION 3.22)
project(lab4)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(CSVParser)
add_executable(lab4 main.cpp Tests.cpp CSVParser/CSVParser.cpp CSVParser/CSVParser.h)
target_include_directories(lab4 PRIVATE CSVParser)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_link_libraries(lab4 PRIVATE Csv_t gtest_main)