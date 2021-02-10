# CMakeLists.txt for DalitzModel module. 
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(SUBPACKAGE DalitzModel)
project(${SUBPACKAGE})

#--- Ensure C++17.
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Ofast -march=native -fPIC")

#--- Define the headers and src directories
file(GLOB_RECURSE sources ./*.cpp)
file(GLOB_RECURSE headers *.h)

#--- Create header only library.
add_library(${SUBPACKAGE} ${sources})