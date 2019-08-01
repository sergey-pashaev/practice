// flipping bits

// https://www.hackerrank.com/challenges/flipping-bits/problem

#include <catch2/catch.hpp>

#include <cstdint>

using namespace std;

long flipping_bits(long n) { return ~((uint32_t)n); }

TEST_CASE("flipping bits") {
    REQUIRE(flipping_bits(0) == 4294967295L);
    REQUIRE(flipping_bits(802743475) == 3492223820L);
    REQUIRE(flipping_bits(35601423) == 4259365872L);
}
