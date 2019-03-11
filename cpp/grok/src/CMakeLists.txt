cmake_minimum_required(VERSION 3.1..3.11)

add_executable(binary_search binary_search.cpp)
target_link_libraries(binary_search catch2)
add_test(NAME binary_search COMMAND binary_search)

add_executable(bfs bfs.cpp)
target_link_libraries(bfs catch2)
add_test(NAME bfs COMMAND bfs)
