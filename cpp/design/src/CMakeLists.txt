cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

function(add_example FILE)
  add_executable("${FILE}" "${FILE}.cpp")
  target_link_libraries("${FILE}" PRIVATE catch2)
  add_test(NAME "${FILE}" COMMAND "${FILE}")
endfunction()

add_example(static_assert)
add_example(interface_adapter)
add_example(select_type)
