# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/user/CLionProjects/lab2/cmake-build-debug/_deps/googletest-src"
  "/home/user/CLionProjects/lab2/cmake-build-debug/_deps/googletest-build"
  "/home/user/CLionProjects/lab2/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "/home/user/CLionProjects/lab2/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/home/user/CLionProjects/lab2/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/home/user/CLionProjects/lab2/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/home/user/CLionProjects/lab2/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/user/CLionProjects/lab2/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
