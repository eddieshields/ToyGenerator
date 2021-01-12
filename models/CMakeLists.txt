set(SUBPACKAGE DalitzModel)

#--- Define the headers and src directories
file(GLOB_RECURSE sources dalitzmodel/*.cpp)
file(GLOB_RECURSE headers dalitzmodel/*.h)

ROOT_GENERATE_DICTIONARY(G__${SUBPACKAGE} ${headers} LINKDEF dict/${SUBPACKAGE}LinkDef.h)

#--- Generate ROOT library from dictionary
add_library(${SUBPACKAGE} SHARED ${sources} ${} G__${SUBPACKAGE}.cxx)