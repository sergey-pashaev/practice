cmake_minimum_required(VERSION 3.1)

add_executable(stl stl.cpp)
target_link_libraries(stl catch2 pthread)
add_test(NAME stl COMMAND stl)
