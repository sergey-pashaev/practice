// reverse integer

// https://leetcode.com/problems/reverse-integer/

// Given a 32-bit signed integer, reverse digits of an integer.

// Example 1:

// Input: 123
// Output: 321
// Example 2:

// Input: -123
// Output: -321
// Example 3:

// Input: 120
// Output: 21

// Note: Assume we are dealing with an environment which could only
// store integers within the 32-bit signed integer range: [−2^31, 2^31 −
// 1]. For the purpose of this problem, assume that your function
// returns 0 when the reversed integer overflows.

#include <catch2/catch.hpp>

#include <limits>

using namespace std;

int reverse(int x) {
    const int base = 10;
    const int min = numeric_limits<int>::min() / base;
    const int max = numeric_limits<int>::max() / base;

    int ret = 0;
    while (x != 0) {
        int digit = x % base;
        x /= base;

        // check for overflow
        if (ret > max) return 0;
        if (ret < min) return 0;

        ret = ret * base + digit;
    }
    return ret;
}

TEST_CASE("reverse integer") {
    REQUIRE(reverse(123) == 321);
    REQUIRE(reverse(-123) == -321);
    REQUIRE(reverse(120) == 21);
    REQUIRE(reverse(numeric_limits<int>::max()) == 0);
    REQUIRE(reverse(numeric_limits<int>::min()) == 0);
    REQUIRE(reverse(2147483647) == 0);
    REQUIRE(reverse(1534236469) == 9656324351);
}
