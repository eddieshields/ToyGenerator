cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(ALGORITHMS Algorithms)
project(${ALGORITHMS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native -flto")

# Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist)

#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Define the header and src directories
file(GLOB_RECURSE HEADERS ${ALGORITHMS}/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp)

ROOT_GENERATE_DICTIONARY(G__${ALGORITHMS} ${HEADERS} LINKDEF dict/${ALGORITHMS}LinkDef.h)

#--- Generate library with ROOT dictionary
add_library(${ALGORITHMS} SHARED ${SOURCES} ${} G__${ALGORITHMS}.cxx)
target_link_libraries(${ALGORITHMS} HydraCore Utils DalitzModel ${ROOT_LIBRARIES} ${CMAKE_DL_LIBS})