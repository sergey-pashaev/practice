// number of 1 bits

// https://leetcode.com/problems/number-of-1-bits/

#include <catch2/catch.hpp>

#include <cstdint>

using namespace std;

int hamming_weight(uint32_t n) {
    int r = 0;
    while (n > 0) {
        r += n & 1;
        n >>= 1;
    }
    return r;
}

TEST_CASE("number of 1 bits") {
    REQUIRE(hamming_weight(0b00000000000000000000000000001011) == 3);
    REQUIRE(hamming_weight(0b00000000000000000000000010000000) == 1);
    REQUIRE(hamming_weight(0b11111111111111111111111111111101) == 31);
}
