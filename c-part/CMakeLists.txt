# cmake_minimum_required(VERSION <specify CMake version here>)
project(c_example)
cmake_minimum_required(VERSION 3.9)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_library(c_example SHARED library.cpp library.h ExampleJni.cpp ExampleJni.h)

set_target_properties(c_example PROPERTIES COMPILE_FLAGS "-march=x86-64" LINK_FLAGS "-march=x86-64")