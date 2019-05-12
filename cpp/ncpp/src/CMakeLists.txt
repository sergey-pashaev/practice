cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

add_library(ncpp ncurses.cpp window.cpp)
target_link_libraries(ncpp PRIVATE ncurses)
target_include_directories(ncpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
