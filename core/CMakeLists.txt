# CMakeLists.txt for ToyGenerator module. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(CORE HydraCore)
project(${CORE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native -flto")

set(CMAKE_CXX_STANDARD 17)
# Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist EG)

#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Find threads.
find_package(Threads REQUIRED)

#--- Define the header and src directories
file(GLOB_RECURSE CORE_HEADERS ${CORE}/*.h)
file(GLOB_RECURSE CORE_SOURCES src/*.cpp)

ROOT_GENERATE_DICTIONARY(G__${CORE} ${CORE_HEADERS} LINKDEF dict/${CORE}LinkDef.h)

#--- Generate library with ROOT dictionary
add_library(${CORE} SHARED ${CORE_SOURCES} ${} G__${CORE}.cxx)
target_link_libraries(${CORE} Utils ${ROOT_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})