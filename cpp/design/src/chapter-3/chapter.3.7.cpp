#include <catch2/catch.hpp>

#include <chapter-3/typelist.h>

namespace c_3_7 {

namespace {

TEST_CASE("IndexOf") {
    // Negative
    REQUIRE(IndexOf<NullType, int>::value == -1);
    REQUIRE(IndexOf<TYPELIST_1(int), double>::value == -1);
    REQUIRE(IndexOf<TYPELIST_3(int, char, double), float>::value == -1);

    // Positive
    REQUIRE(IndexOf<TYPELIST_1(int), int>::value == 0);
    REQUIRE(IndexOf<TYPELIST_2(int, char), char>::value == 1);
    REQUIRE(IndexOf<TYPELIST_3(int, char, double), double>::value == 2);

}

}  // namespace

} // namespace c_3_7
