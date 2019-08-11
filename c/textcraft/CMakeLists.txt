cmake_minimum_required(VERSION 3.1)

project(textcraft C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(USE_CCACHE "Use ccache if available" ON)
if(USE_CCACHE)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  endif()
endif()

add_definitions(-ggdb3)
add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-std=c11)
add_definitions(-pedantic)
add_definitions(-fsanitize=address)

add_executable(getline getline.c)
target_link_libraries(getline PRIVATE asan)
