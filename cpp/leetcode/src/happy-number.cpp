// happy number

// https://leetcode.com/problems/happy-number/

#include <catch2/catch.hpp>

#include <set>

using namespace std;

int digits_squared(int n) {
    int base = 10;
    int sum = 0;
    while (n > 0) {
        int digit = n % base;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

bool is_happy(int n) {
    set<int> sums;

    int sum = 0;
    for (;;) {
        sum = digits_squared(n);
        if (sum == 1) return true;
        if (sums.count(sum)) return false;

        sums.insert(sum);
        n = sum;
    }

    return false;
}

bool is_happy_fast(int n) {
    int slow = n;
    int fast = n;

    do {
        slow = digits_squared(slow);
        fast = digits_squared(fast);
        fast = digits_squared(fast);
    } while (slow != fast);
    return slow == 1;
}

TEST_CASE("happy number O(n) space") {
    REQUIRE(is_happy(1));
    REQUIRE(is_happy(19));
    REQUIRE(!is_happy(0));
}

TEST_CASE("happy number O(1) space") {
    REQUIRE(is_happy_fast(1));
    REQUIRE(is_happy_fast(19));
    REQUIRE(!is_happy_fast(0));
}
