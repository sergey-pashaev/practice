cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

add_executable(stl stl.cpp)
target_link_libraries(stl catch2 pthread)
add_test(NAME stl COMMAND stl)
