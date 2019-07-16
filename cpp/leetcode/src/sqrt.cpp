// sqrt

// Implement int sqrt(int x).

// Compute and return the square root of x, where x is guaranteed to be a
// non-negative integer.

// Since the return type is an integer, the decimal digits are truncated and
// only the integer part of the result is returned.

// Example 1:
// Input: 4
// Output: 2

// Example 2:
// Input: 8
// Output: 2
// Explanation: The square root of 8 is 2.82842..., and since
//              the decimal part is truncated, 2 is returned.

#include <catch2/catch.hpp>

#include <cmath>

using namespace std;

bool good(double guess, int x) { return abs((guess * guess) - x) < 0.001; }

double improve(double guess, int x) { return (guess + x / guess) / 2.0; }

int my_sqrt(int x) {
    double guess = 1.0;
    while (!good(guess, x)) {
        guess = improve(guess, x);
    }
    return guess;
}

TEST_CASE("sqrt") {
    REQUIRE(my_sqrt(2) == 1);
    REQUIRE(my_sqrt(4) == 2);
    REQUIRE(my_sqrt(8) == 2);
    REQUIRE(my_sqrt(9) == 3);
}
