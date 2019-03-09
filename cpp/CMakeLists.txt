cmake_minimum_required(VERSION 3.1..3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

add_definitions(-std=c++11)
add_definitions(-O3)
add_definitions(-ggdb3)
add_definitions(-Wall)
add_definitions(-Wextra)

include_directories(thirdparty)

add_subdirectory(algo)
add_subdirectory(ciu)
add_subdirectory(thirdparty)
