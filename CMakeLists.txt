# CMakeLists.txt for ToyGenerator module. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(PACKAGE Hydra)
project(${PACKAGE})

set (CMAKE_CXX_STANDARD 17)
option(TOYGEN_DEBUG "AmpGen Debug printout")
SET(USE_OPENMP TRUE CACHE BOOL "USE_OPENMP")

# Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RIO Hist Graf Graf3d Postscript Gpad
                             RooFit RooFitCore Tree MathCore Foam Physics
                             Proof ProofBench ProofDraw ProofPlayer)

#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Use Boost
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#--- Use Python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

#--- Define the headers list
include_directories(include src dict algorithms models/dalitzmodel  ${CMAKE_SOURCE_DIR})

if (APPLE)
    include_directories(external/json/single_include)
endif()

#--- Define the headers and src directories
file(GLOB_RECURSE sources src/*.cpp algorithms/*.cpp models/dalitzmodel/*.cpp)
file(GLOB_RECURSE headers include/*.h algorithms/*.h models/dalitzmodel/*.h)

ROOT_GENERATE_DICTIONARY(G__${PACKAGE} ${headers} LINKDEF dict/${PACKAGE}LinkDef.h)

#--- Generate library with ROOT dictionary
add_library(${PACKAGE} SHARED ${sources} ${} G__${PACKAGE}.cxx)

#--- Use OpenMP
if ( USE_OPENMP )
    find_package(OpenMP)
    if (OpenMP_CXX_FOUND)
        target_link_libraries(${PACKAGE} PUBLIC OpenMP::OpenMP_CXX ${ROOT_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CMAKE_DL_LIBS} ${PYTHON_LIBRARIES})
    else()
        message(STATUS "OpenMP not found for CXX, you might have forgotten lb-run ROOT bash or CXX=`which g++` in CERN stack")
    endif()
else()
    target_link_libraries(${PACKAGE} ${ROOT_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${CMAKE_DL_LIBS} ${PYTHON_LIBRARIES})
endif()

#--- External library for reading json files.
target_include_directories(${PACKAGE} PUBLIC external/json/single_include)

#--- Create an executable
add_executable(ToyGenerator ${CMAKE_SOURCE_DIR}/apps/ToyGenerator.cpp)
target_link_libraries(ToyGenerator ${PACKAGE})

add_executable(getFraction ${CMAKE_SOURCE_DIR}/apps/getFraction.cpp)
target_link_libraries(getFraction ${PACKAGE})

if (OpenMP_CXX_FOUND)
    add_executable(getMaxThreads ${CMAKE_SOURCE_DIR}/apps/getMaxThreads.cpp)
    target_link_libraries(getMaxThreads PUBLIC OpenMP::OpenMP_CXX)
endif()

#--- Create Hydra
execute_process(COMMAND chmod +x ${CMAKE_SOURCE_DIR}/Hydra)
