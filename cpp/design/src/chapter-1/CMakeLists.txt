cmake_minimum_required(VERSION 3.1)

add_example(creator)
add_example(static_assert)
add_example(interface_adapter)
add_example(select_type)

expect_segfault(creator C17_PUBLIC_DTOR)
expect_compilation_failure(creator C17_PROTECTED_DTOR)
