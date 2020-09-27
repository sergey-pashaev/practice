cmake_minimum_required(VERSION 3.1)

function(add_example FILE)
  add_executable("${FILE}" "${FILE}.cpp")
  target_link_libraries("${FILE}" PRIVATE catch2)
  add_test(NAME "${FILE}" COMMAND "${FILE}")
endfunction()

add_subdirectory(utils)

add_subdirectory(chapter-1)
