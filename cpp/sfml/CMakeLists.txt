cmake_minimum_required(VERSION 3.1)

project(sfml)

find_package(GLM REQUIRED)

add_executable(sfml main.cpp)
message("${CONAN_LIBS}")
target_link_libraries(sfml PRIVATE sfml-graphics-s-d sfml-window-s-d sfml-system-s-d Xrandr Xext Xrender X11 pthread xcb Xau Xdmcp GL udev termcap elf lzma freetyped png16d m bz2 z)
target_link_libraries(sfml PRIVATE GLEWd)
