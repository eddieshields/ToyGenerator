# CMakeLists.txt for ToyGenerator module. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
set(PACKAGE HYDRA)
project(${PACKAGE})

include_directories(utils/include)
add_subdirectory(utils)

#include_directories(algorithms/include)
#add_subdirectory(algorithms)
#
#include_directories(models/dalitzmodel/include)
#add_subdirectory(models)

# Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist)

#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

include_directories(core/include)

#--- Include external JSON library needed.
# Fix this section of compilation for lxplus.
include_directories(${CMAKE_SOURCE_DIR}/external/json/single_include)

#--- Define the header and src directories
file(GLOB_RECURSE HEADERS core/include/*.h)
file(GLOB_RECURSE SOURCES core/Core/*.cpp)

ROOT_GENERATE_DICTIONARY(G__${PACKAGE} ${HEADERS} LINKDEF core/dict/CoreLinkDef.h)

#--- Generate library with ROOT dictionary
add_library(${PACKAGE} SHARED ${SOURCES} ${} G__${PACKAGE}.cxx)
target_link_libraries(${PACKAGE} ${ROOT_LIBRARIES} ${CMAKE_DL_LIBS})
#--- Link libraries
#target_link_libraries(${PACKAGE} Utils Algorithms DalitzModel ${ROOT_LIBRARIES} ${CMAKE_DL_LIBS})
#
##--- Create an executable
#add_executable(ToyGenerator ${CMAKE_SOURCE_DIR}/apps/ToyGenerator.cpp)
#target_link_libraries(ToyGenerator ${PACKAGE})
#
##--- Create Hydra
#execute_process(COMMAND chmod +x ${CMAKE_SOURCE_DIR}/Hydra)
