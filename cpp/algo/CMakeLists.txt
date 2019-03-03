cmake_minimum_required(VERSION 3.1..3.11)

project(algo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

add_definitions(-ggdb3)
add_definitions(-Wall)
add_definitions(-Wextra)

include_directories(src)
include_directories(thirdparty)

add_subdirectory(src)
add_subdirectory(thirdparty)
