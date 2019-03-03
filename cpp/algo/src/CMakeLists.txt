cmake_minimum_required(VERSION 3.1..3.11)

add_executable(heapsort heapsort.cpp)
target_link_libraries(heapsort catch2)
add_test(NAME heapsort COMMAND heapsort)
