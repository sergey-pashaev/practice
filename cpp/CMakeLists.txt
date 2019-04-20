cmake_minimum_required(VERSION 3.1..3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-Wall)
add_definitions(-Wextra)

include_directories(thirdparty)
add_subdirectory(thirdparty)

add_subdirectory(algo)
add_subdirectory(ciu)
add_subdirectory(grok)
