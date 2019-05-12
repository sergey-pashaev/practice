cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

add_executable(editor app.cpp frame.cpp buffer.cpp editor.cpp)
target_link_libraries(editor PRIVATE ncpp)
