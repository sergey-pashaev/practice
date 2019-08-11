cmake_minimum_required(VERSION 3.1)

add_library(ncpp ncurses.cpp window.cpp)
target_link_libraries(ncpp PRIVATE ncurses)
target_include_directories(ncpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
