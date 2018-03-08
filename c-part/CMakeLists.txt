# cmake_minimum_required(VERSION <specify CMake version here>)
project(c_example)
cmake_minimum_required(VERSION 3.9)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_library(c_example SHARED library.cpp library.h ExampleJni.h ExampleJni.cpp handle.h PluginLoader.h Plugin.h PluginJni.h PluginLoaderJni.h BaseJniClassJni.h PluginLoaderJni.cpp PluginJni.cpp BaseJniClass.cpp Plugin.cpp handle.cpp)

set_target_properties(c_example PROPERTIES CMAKE_EXE_LINKER_FLAGS "-static" COMPILE_FLAGS "-march=x86-64 -static-libgcc -static-libstdc++" LINK_FLAGS "-march=x86-64")

