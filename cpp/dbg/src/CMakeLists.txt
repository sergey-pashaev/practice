cmake_minimum_required(VERSION 3.1)

add_executable(dbg-dbg dbg.cpp breakpoint.cpp debugger.cpp utils.cpp)
set_target_properties(dbg-dbg PROPERTIES OUTPUT_NAME dbg)
