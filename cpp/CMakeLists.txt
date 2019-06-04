cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(USE_CCACHE "Use ccache if available" ON)
if(USE_CCACHE)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  endif()
endif()

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_definitions(-Wall)
add_definitions(-Wextra)

add_subdirectory(thirdparty)

add_subdirectory(algo)
add_subdirectory(adt)
add_subdirectory(ciu)
add_subdirectory(design)
add_subdirectory(editor)
add_subdirectory(grok)
add_subdirectory(ncpp)
add_subdirectory(idiom)
