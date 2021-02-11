cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
set(SUBPACKAGE Algorithms)
project(${SUBPACKAGE})

# Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist)

#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Define the headers list
include_directories(include)

#--- Define the header and src directories
file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB_RECURSE SOURCES ${SUBPACKAGE}/*.cpp)

ROOT_GENERATE_DICTIONARY(G__${SUBPACKAGE} ${HEADERS} LINKDEF dict/${SUBPACKAGE}LinkDef.h)

#--- Generate library with ROOT dictionary
add_library(${SUBPACKAGE} SHARED ${SOURCES} ${} G__${SUBPACKAGE}.cxx)