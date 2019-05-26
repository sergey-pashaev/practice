cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

add_executable(circular_buffer circular_buffer.cpp)
target_link_libraries(circular_buffer catch2)
add_test(NAME circular_buffer COMMAND circular_buffer)
