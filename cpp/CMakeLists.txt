cmake_minimum_required(VERSION 3.1)

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
  add_executable("${PROJECT_NAME}-${NAME}" "${NAME}.cpp")
  set_target_properties("${PROJECT_NAME}-${NAME}" PROPERTIES OUTPUT_NAME "${NAME}")
endfunction()

function(testable NAME)
  add_executable("${PROJECT_NAME}-${NAME}" "${NAME}.cpp")
  target_link_libraries("${PROJECT_NAME}-${NAME}" PRIVATE catch2)
  set_target_properties("${PROJECT_NAME}-${NAME}" PROPERTIES OUTPUT_NAME "${NAME}")
  add_test(NAME "${PROJECT_NAME}-${NAME}" COMMAND "${NAME}")
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
add_subdirectory(idiom)
add_subdirectory(leetcode)
add_subdirectory(ncpp)
add_subdirectory(stepik)
add_subdirectory(stl)
add_subdirectory(ya)
