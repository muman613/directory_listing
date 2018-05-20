cmake_minimum_required(VERSION 3.10)
project(dirlist)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

add_executable(dirlist main.cpp directorylist.cpp directorylist.h directory_enumerator.h directory_enumerator.cpp)