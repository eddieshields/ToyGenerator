# CMakeLists.txt for ToyGenerator module. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(DALITZMODEL DalitzModel)
project(${DALITZMODEL})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native -flto")

# Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist)

#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Define the header and src directories
file(GLOB_RECURSE HEADERS ${DALITZMODEL}/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp)

ROOT_GENERATE_DICTIONARY(G__${DALITZMODEL} ${HEADERS} LINKDEF dict/${DALITZMODEL}LinkDef.h)

#--- Generate library with ROOT dictionary
add_library(${DALITZMODEL} SHARED ${SOURCES} ${} G__${DALITZMODEL}.cxx)
target_link_libraries(${DALITZMODEL} Utils ${ROOT_LIBRARIES})