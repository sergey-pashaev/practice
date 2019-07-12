// palindrome number

// https://leetcode.com/problems/palindrome-number/

// Determine whether an integer is a palindrome. An integer is a
// palindrome when it reads the same backward as forward.

// Example 1:

// Input: 121
// Output: true

// Example 2:

// Input: -121
// Output: false

// Explanation: From left to right, it reads -121. From right to left,
// it becomes 121-. Therefore it is not a palindrome.

// Example 3:

// Input: 10
// Output: false

// Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

// Follow up: Coud you solve it without converting the integer to a
// string?

#include <catch2/catch.hpp>

#include <limits>

using namespace std;

int reverse(int x) {
    const int base = 10;
    const int max = numeric_limits<int>::max() / base;
    const int min = numeric_limits<int>::min() / base;
    int ret = 0;
    while (x != 0) {
        int digit = x % base;
        x /= base;

        if (ret > max) return 0;
        if (ret < min) return 0;
        ret = ret * base + digit;
    }
    return ret;
}

bool is_palindrome(int x) {
    if (x < 0) return false;
    return reverse(x) == x;
}

TEST_CASE("palindrome number") {
    REQUIRE(is_palindrome(121));
    REQUIRE(!is_palindrome(-121));
    REQUIRE(!is_palindrome(10));
}
