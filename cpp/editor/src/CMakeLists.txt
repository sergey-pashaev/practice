cmake_minimum_required(VERSION 3.1)

add_executable(editor app.cpp frame.cpp buffer.cpp editor.cpp)
target_link_libraries(editor PRIVATE ncpp)
