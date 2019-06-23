cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

function(runnable NAME)
  add_executable("${NAME}" "${NAME}.cpp")
endfunction()

function(testable NAME)
  add_executable("${NAME}" "${NAME}.cpp")
  target_link_libraries("${NAME}" catch2)
  add_test(NAME "${NAME}" COMMAND "${NAME}")
endfunction()

runnable(ex.1.1)
testable(ex.1.2)
testable(ex.1.3)
testable(ex.1.4)
testable(ex.1.5)
