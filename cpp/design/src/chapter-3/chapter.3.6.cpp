#include <catch2/catch.hpp>

#include <type_traits>

#include <chapter-3/typelist.h>

namespace c_3_6 {

namespace {

TEST_CASE("TypeAt") {
    REQUIRE(std::is_same<TypeAt<TYPELIST_1(int), 0>::Result, int>::value);
    REQUIRE(std::is_same<TypeAt<TYPELIST_3(int, char, double), 1>::Result,
                         char>::value);
    REQUIRE(std::is_same<TypeAt<TYPELIST_3(int, char, double), 2>::Result,
                         double>::value);
}

}  // namespace

}  // namespace c_3_6
