cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(TEST Test)
project(${TEST})

file(GLOB TEST_SRC CONFIGURE_DEPENDS "*.cpp")

add_executable(${TEST} ${TEST_SRC})
target_link_libraries(${TEST} HYDRA)