cmake_minimum_required(VERSION 3.0.0)

project(puzzles)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif()

include(precompiled_header.cmake)

file(GLOB_RECURSE sources *.cpp)
add_executable(main ${sources})

add_precompiled_header(main ${CMAKE_CURRENT_SOURCE_DIR}/precompiled.h ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

enable_testing()
add_test(NAME tests COMMAND main)
