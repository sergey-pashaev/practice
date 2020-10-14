cmake_minimum_required(VERSION 3.1)

project(cpp)

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
function(runnable FILE)
  set(name "${PROJECT_NAME}-${FILE}")
  add_executable("${name}" "${FILE}.cpp")
  set_target_properties("${name}" PROPERTIES OUTPUT_NAME "${FILE}")
endfunction()

function(unit_test FILE)
  set(name "unit_test.${PROJECT_NAME}-${FILE}")
  add_executable("${name}" "${FILE}.cpp")
  target_link_libraries("${name}" PRIVATE catch2 pthread)
  set_target_properties("${name}" PROPERTIES OUTPUT_NAME "${FILE}")
  add_test(NAME "${name}" COMMAND "${FILE}")
  set_tests_properties("${name}" PROPERTIES LABELS "unit_test")
endfunction()

# subprojects
add_subdirectory(thirdparty)

add_subdirectory(adt)
add_subdirectory(algo)
add_subdirectory(ciu)
add_subdirectory(dbg)
add_subdirectory(dcp)
add_subdirectory(design)
add_subdirectory(editor)
add_subdirectory(exceptional)
add_subdirectory(grok)
add_subdirectory(hackerrank)
add_subdirectory(idiom)
add_subdirectory(leetcode)
add_subdirectory(ncpp)
add_subdirectory(stepik)
add_subdirectory(stl)
add_subdirectory(stroustrup)
add_subdirectory(ya)
