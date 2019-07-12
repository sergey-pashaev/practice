cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

# global definitions
add_definitions(-Wall)
add_definitions(-Wextra)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ccache
option(USE_CCACHE "Use ccache if available" ON)
if(USE_CCACHE)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  endif()
endif()

# ctest
include(CTest)

# conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

# functions
function(runnable NAME)
  add_executable("${NAME}" "${NAME}.cpp")
endfunction()

function(testable NAME)
  add_executable("${NAME}" "${NAME}.cpp")
  target_link_libraries("${NAME}" PRIVATE catch2)
  add_test(NAME "${NAME}" COMMAND "${NAME}")
endfunction()

# subprojects
add_subdirectory(thirdparty)

add_subdirectory(adt)
add_subdirectory(algo)
add_subdirectory(ciu)
add_subdirectory(dcp)
add_subdirectory(design)
add_subdirectory(editor)
add_subdirectory(exceptional)
add_subdirectory(grok)
add_subdirectory(hackerrank)
add_subdirectory(leetcode)
add_subdirectory(idiom)
add_subdirectory(ncpp)
add_subdirectory(stl)
