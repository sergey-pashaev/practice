cmake_minimum_required(VERSION 3.1..3.11)

add_executable(vector vector.cpp)
target_link_libraries(vector catch2)
add_test(NAME vector COMMAND vector)
