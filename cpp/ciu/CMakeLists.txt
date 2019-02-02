cmake_minimum_required(VERSION 3.1..3.11)

project(ciu)

include(CTest)

include_directories(include)
include_directories(src)
include_directories(thirdparty)

add_subdirectory(src)
add_subdirectory(thirdparty)
