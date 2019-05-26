cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

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
add_subdirectory(adt)
add_subdirectory(ciu)
add_subdirectory(design)
add_subdirectory(editor)
add_subdirectory(grok)
add_subdirectory(ncpp)
