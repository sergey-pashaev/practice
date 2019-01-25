cmake_minimum_required(VERSION 3.1..3.11)

project(knr)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(USE_CCACHE "Use ccache if available" ON)
if(USE_CCACHE)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  endif()
endif()

option(USE_KCOV "Use kcov if available" ON)
if(USE_KCOV)
  find_program(KCOV_PROGRAM kcov)
  set(KCOV_ARGS "--exclude-pattern=/usr/include,thirdparty,/usr/lib")
  set(KCOV_REPORT_PATH "/tmp/kcov-${PROJECT_NAME}")
endif()

function(ex)
  set(args NUMBER)
  set(lists FILES)
  cmake_parse_arguments(EX "" "${args}" "${lists}" ${ARGN})
  set(name "ex.${EX_NUMBER}")
  add_executable("${name}" "${EX_FILES}")
endfunction()

function(resource FILE)
  configure_file("${FILE}" "${FILE}" COPYONLY)
endfunction()

add_subdirectory(src)
