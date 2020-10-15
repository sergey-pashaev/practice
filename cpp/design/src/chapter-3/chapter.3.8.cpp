#include <catch2/catch.hpp>

#include <type_traits>

#include <chapter-3/typelist.h>

namespace c_3_8 {

namespace {

TEST_CASE("Append") {
    REQUIRE(
        std::is_same<Append<NullType, int>::Result, TYPELIST_1(int)>::value);
    REQUIRE(std::is_same<Append<TYPELIST_1(int), char>::Result,
                         TYPELIST_2(int, char)>::value);
    REQUIRE(
        std::is_same<Append<TYPELIST_1(int), TYPELIST_2(char, float)>::Result,
                     TYPELIST_3(int, char, float)>::value);
}

}  // namespace

}  // namespace c_3_8
