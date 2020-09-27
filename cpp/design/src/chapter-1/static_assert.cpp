#include <catch2/catch.hpp>

// declare template
template <bool>
struct CompileTimeError;

// Specialize for true to do nothing. There is no specialization for
// false - so it should not compile.
template <>
struct CompileTimeError<true> {};

// #define STATIC_ASSERT(expr) (CompileTimeError<(expr) != 0>())

// try to declare & use variable of compile time error type
#define STATIC_ASSERT(expr, msg)                     \
    {                                                \
        CompileTimeError<((expr) != 0)> ERROR_##msg; \
        (void)ERROR_##msg;                           \
    }

TEST_CASE("static assert true") { STATIC_ASSERT(true, hello); }

// should not compile
// TEST_CASE("static assert false") {
//     STATIC_ASSERT(sizeof(char) > sizeof(void*), size_mismatch);
// }
