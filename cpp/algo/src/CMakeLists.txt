cmake_minimum_required(VERSION 3.1..3.11)

add_executable(heapsort heapsort.cpp)
target_link_libraries(heapsort catch2)
add_test(NAME heapsort COMMAND heapsort)

add_executable(mergesort mergesort.cpp)
target_link_libraries(mergesort catch2)
add_test(NAME mergesort COMMAND mergesort)

add_executable(bubblesort bubblesort.cpp)
target_link_libraries(bubblesort catch2)
add_test(NAME bubblesort COMMAND bubblesort)

add_executable(selectionsort selectionsort.cpp)
target_link_libraries(selectionsort catch2)
add_test(NAME selectionsort COMMAND selectionsort)
