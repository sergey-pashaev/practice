cmake_minimum_required(VERSION 3.1..3.11)

add_executable(static_assert static_assert.cpp)
target_link_libraries(static_assert PRIVATE catch2)
add_test(NAME static_assert COMMAND static_assert)
