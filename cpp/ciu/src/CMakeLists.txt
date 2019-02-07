cmake_minimum_required(VERSION 3.1..3.11)

add_executable(vector vector.cpp)
target_link_libraries(vector catch2)
add_test(NAME vector COMMAND vector)

add_executable(linked_list linked_list.cpp)
target_link_libraries(linked_list catch2)
add_test(NAME linked_list COMMAND linked_list)
