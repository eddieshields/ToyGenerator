# CMakeLists.txt for ToyGenerator module. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
set(PACKAGE HYDRA)
project(${PACKAGE})

#--- Include core directory
include_directories(core/include)

# Fix this section of compilation for lxplus.
include_directories(external/json/single_include)
if (APPLE)
    include_directories(external/json/single_include)
endif()

#--- Include Utils
include_directories(utils/Utils)
add_subdirectory(utils)

#--- Include Core
include_directories(core/Core)
add_subdirectory(core)

#--- Include DalitzModel
include_directories(models/dalitzmodel/DalitzModel)
add_subdirectory(models)

#--- Include Algorithms
include_directories(algorithms/Algorithms)
add_subdirectory(algorithms)

# Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist)

#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Define the header and src directories
file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp)

ROOT_GENERATE_DICTIONARY(G__${PACKAGE} ${HEADERS} LINKDEF dict/${PACKAGE}LinkDef.h)

#--- Generate library with ROOT dictionary
add_library(${PACKAGE} SHARED ${SOURCES} ${} G__${PACKAGE}.cxx)

#--- Link libraries
target_link_libraries(${PACKAGE} Utils Core DalitzModel Algorithms ${ROOT_LIBRARIES} ${CMAKE_DL_LIBS})

#--- Link libraries
include_directories(external/cxxopts/include)

##--- Create an executable
add_executable(ToyGenerator ${CMAKE_SOURCE_DIR}/apps/ToyGenerator.cpp)
target_link_libraries(ToyGenerator ${PACKAGE})

##--- Create an executable
add_executable(PlotDalitzModel ${CMAKE_SOURCE_DIR}/apps/PlotDalitzModel.cpp)
target_link_libraries(PlotDalitzModel ${PACKAGE})