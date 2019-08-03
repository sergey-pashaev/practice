// reverse bits

#include <catch2/catch.hpp>

#include <cstdint>

using namespace std;

uint32_t reverse_bits(uint32_t n) {
    const int c = sizeof(n) * 8;
    uint32_t r = 0;

    // just copy all bits from last to one
    for (int i = 0; i < c; ++i) {
        r = (r << 1) + ((n >> i) & 1);
    }

    return r;
}

TEST_CASE("reverse bits") {
    REQUIRE(reverse_bits(0b00000010100101000001111010011100) ==
            0b00111001011110000010100101000000);

    REQUIRE(reverse_bits(0b11111111111111111111111111111101) ==
            0b10111111111111111111111111111111);
}
