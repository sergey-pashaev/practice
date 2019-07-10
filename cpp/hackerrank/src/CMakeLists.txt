cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

testable(sock-merchant)
testable(counting-valleys)
testable(jumping-on-the-clouds)
