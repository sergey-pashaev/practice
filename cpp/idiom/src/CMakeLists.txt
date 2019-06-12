cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()


add_executable(loggable loggable.cpp)

add_executable(clonable clonable.cpp)

add_executable(badge badge.cpp)
