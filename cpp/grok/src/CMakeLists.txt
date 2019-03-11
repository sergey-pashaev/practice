cmake_minimum_required(VERSION 3.1..3.11)

add_executable(binary_search binary_search.cpp)
target_link_libraries(binary_search catch2)
add_test(NAME binary_search COMMAND binary_search)

add_executable(bfs bfs.cpp)
target_link_libraries(bfs catch2)
add_test(NAME bfs COMMAND bfs)

add_executable(dijkstra dijkstra.cpp)
target_link_libraries(dijkstra catch2)
add_test(NAME dijkstra COMMAND dijkstra)

add_executable(set_cover_greedy set_cover_greedy.cpp)
target_link_libraries(set_cover_greedy catch2)
add_test(NAME set_cover_greedy COMMAND set_cover_greedy)

add_executable(knapsack knapsack.cpp)
target_link_libraries(knapsack catch2)
add_test(NAME knapsack COMMAND knapsack)
