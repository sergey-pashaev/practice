cmake_minimum_required(VERSION 3.1)

add_executable(dbg-dbg dbg.cpp breakpoint.cpp debugger.cpp utils.cpp registers.cpp dwarf_reader.cpp)
target_link_libraries(dbg-dbg PRIVATE ${CONAN_LIBS})
target_link_libraries(dbg-dbg PRIVATE fmtd)
set_target_properties(dbg-dbg PROPERTIES OUTPUT_NAME dbg)

add_executable(dbg-test test.cpp)
set_target_properties(dbg-test PROPERTIES OUTPUT_NAME test)
