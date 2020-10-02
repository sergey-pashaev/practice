cmake_minimum_required(VERSION 3.1)

add_executable(expect_segfault expect_segfault.c)

# https://stackoverflow.com/questions/33693486/how-can-i-use-cmake-to-test-processes-that-are-expected-to-fail-with-an-exceptio
function(expect_segfault FILE TESTNAME)
  set(name "runtime-failure.${FILE}.${TESTNAME}")
  set(test_name "test.${name}")
  add_executable("${name}" "${FILE}.cpp")
  target_link_libraries("${name}" PRIVATE catch2 pthread)
  target_compile_definitions("${name}" PRIVATE "${TESTNAME}")
  add_test(NAME "${test_name}"
    COMMAND $<TARGET_FILE:expect_segfault> $<TARGET_FILE:${name}>
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endfunction()

# https://stackoverflow.com/questions/30155619/expected-build-failure-tests-in-cmake
function(expect_compilation_failure FILE TESTNAME)
  set(name "compilation-failure.${FILE}.${TESTNAME}")
  set(test_name "test.${name}")
  add_executable("${name}" "${FILE}.cpp")
  target_link_libraries("${name}" PRIVATE catch2 pthread)
  set_target_properties("${name}" PROPERTIES
    EXCLUDE_FROM_ALL TRUE
    EXCLUDE_FROM_DEFAULT_BUILD TRUE)
  target_compile_definitions("${name}" PRIVATE "${TESTNAME}")
  add_test(NAME "${test_name}"
    COMMAND ${CMAKE_COMMAND} --build . --target "${name}" --config $<CONFIGURATION>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  set_tests_properties("${test_name}" PROPERTIES WILL_FAIL TRUE)
endfunction()
