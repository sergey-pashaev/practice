#include <catch2/catch.hpp>

#include <cstdint>

#include <utils/utils.h>

namespace c_2_1 {

namespace {

#define STATIC_CHECK(expr)            \
    {                                 \
        char unnamed[(expr) ? 1 : 0]; \
        (void)unnamed;                \
    }

template <class To, class From>
To safe_reinterpret_cast(From from) {
    STATIC_CHECK(sizeof(To) >= sizeof(From));
    return reinterpret_cast<To>(from);
}

TEST_CASE("STATIC_CHECK macro") {
    void* ptr = nullptr;

#ifdef POINTER_TO_CHAR_MACRO
    char c = safe_reinterpret_cast<char>(ptr);
    unused(c);
#endif

    uint64_t i = safe_reinterpret_cast<uint64_t>(ptr);
    unused(i);
}

#undef STATIC_CHECK

}  // namespace

namespace {

template <bool>
struct CompileTimeChecker {
    CompileTimeChecker(...) {}
};
template <>
struct CompileTimeChecker<false> {};

#define STATIC_CHECK(expr, msg)                           \
    {                                                     \
        class ERROR_##msg {};                             \
        CompileTimeChecker<(expr) != 0>((ERROR_##msg())); \
    }

template <class To, class From>
To safe_reinterpret_cast2(From from) {
    STATIC_CHECK(sizeof(To) >= sizeof(From), Destination_Type_Too_Narrow);
    return reinterpret_cast<To>(from);
}

TEST_CASE("STATIC_CHECK templates") {
    void* ptr = nullptr;

#ifdef POINTER_TO_CHAR_TEMPLATE
    char c = safe_reinterpret_cast2<char>(ptr);
    unused(c);
#endif

    uint64_t i = safe_reinterpret_cast2<uint64_t>(ptr);
    unused(i);
}
#undef STATIC_CHECK

}  // namespace

}  // namespace c_2_1
