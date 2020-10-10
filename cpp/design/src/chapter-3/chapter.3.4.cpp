#include <catch2/catch.hpp>

#include <chapter-3/typelist.h>

namespace c_3_4 {

namespace {

TEST_CASE("TypeList length") {
    REQUIRE(Length<TYPELIST_3(int, char, double)>::value == 3);
    REQUIRE(Length<TYPELIST_1(int)>::value == 1);
    REQUIRE(Length<NullType>::value == 0);
}

}  // namespace

}  // namespace c_3_4
