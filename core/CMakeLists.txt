# CMakeLists.txt for ToyGenerator module. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
set(SUBPACKAGE Core)
project(${SUBPACKAGE})

set(CMAKE_CXX_STANDARD 17)
# Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist)

#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Define the headers list
include_directories(include)

#--- Include external JSON library needed.
# Fix this section of compilation for lxplus.
include_directories(${CMAKE_SOURCE_DIR}/external/json/single_include)

#--- Find threads.
find_package(Threads REQUIRED)

#--- Define the header and src directories
file(GLOB_RECURSE HEADERS ${SUBPACKAGE}/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp)

ROOT_GENERATE_DICTIONARY(G__${SUBPACKAGE} ${HEADERS} LINKDEF dict/${SUBPACKAGE}LinkDef.h)

#--- Generate library with ROOT dictionary
add_library(${SUBPACKAGE} SHARED ${SOURCES} ${} G__${SUBPACKAGE}.cxx)
target_link_libraries(${SUBPACKAGE} Utils ${ROOT_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})