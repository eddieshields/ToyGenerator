# CMakeLists.txt for ToyGenerator module. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)
set(PACKAGE ToyGen)
project(${PACKAGE})


# Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RIO Hist Graf Graf3d Postscript Gpad
                             RooFit RooFitCore Tree MathCore Foam Physics
                             Proof ProofBench ProofDraw ProofPlayer)


#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Define the headers list
include_directories(include src dict ${CMAKE_SOURCE_DIR})

#--- Define the headers and src directories
file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.h)

ROOT_GENERATE_DICTIONARY(G__${PACKAGE} ${headers} LINKDEF dict/${PACKAGE}LinkDef.h)

#--- Generate ROOT library from dictionary
add_library(ROOT${PACKAGE} SHARED ${sources} G__${PACKAGE}.cxx)

#-- Generate general library
add_library(${PACKAGE} SHARED ${sources} ${headers})


target_link_libraries(ROOT${PACKAGE} ${ROOT_LIBRARIES})
target_link_libraries(${PACKAGE} ${ROOT_LIBRARIES})

#---Create an executable
add_executable(ToyGenerator ${CMAKE_SOURCE_DIR}/apps/ToyGenerator.cpp)
target_link_libraries(ToyGenerator ${PACKAGE})
