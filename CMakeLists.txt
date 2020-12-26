# CMakeLists.txt for ToyGenerator module. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(PACKAGE ToyGen)
project(${PACKAGE})

option(TOYGEN_DEBUG "AmpGen Debug printout")

# Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RIO Hist Graf Graf3d Postscript Gpad
                             RooFit RooFitCore Tree MathCore Foam Physics
                             Proof ProofBench ProofDraw ProofPlayer)

find_package(Boost)
                    
#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

#--- Define the headers list
include_directories(include src dict external/json/single_include ${CMAKE_SOURCE_DIR})

#--- Add json
add_subdirectory(external/json)

#--- Define the headers and src directories
file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.h)
file(GLOB_RECURSE json external/json/single_include/*)

ROOT_GENERATE_DICTIONARY(G__${PACKAGE} ${headers} LINKDEF dict/${PACKAGE}LinkDef.h)

#--- Generate ROOT library from dictionary
add_library(HYDRA SHARED ${sources} G__${PACKAGE}.cxx)

#-- Generate general library
add_library(${PACKAGE} SHARED ${sources} ${headers})

#--- Link libraries
target_link_libraries(HYDRA ${ROOT_LIBRARIES} ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)
target_link_libraries(${PACKAGE} ${ROOT_LIBRARIES} ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)

#---Create an executable
add_executable(ToyGenerator ${CMAKE_SOURCE_DIR}/apps/ToyGenerator.cpp)
target_link_libraries(ToyGenerator ${PACKAGE})

add_executable(test ${CMAKE_SOURCE_DIR}/apps/test.cpp)
target_link_libraries(test ${PACKAGE})