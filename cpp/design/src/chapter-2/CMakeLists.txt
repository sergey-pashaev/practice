cmake_minimum_required(VERSION 3.1)

add_example(chapter.2.1)
expect_compilation_failure(chapter.2.1 POINTER_TO_CHAR_MACRO)
expect_compilation_failure(chapter.2.1 POINTER_TO_CHAR_TEMPLATE)
