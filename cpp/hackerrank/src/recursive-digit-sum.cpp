// recursive digit sum

// https://www.hackerrank.com/challenges/recursive-digit-sum/problem

#include <catch2/catch.hpp>

#include <string>

using namespace std;

long digit_sum(const string& s) {
    long sum = 0;
    for (char c : s) {
        sum += c - '0';
    }
    return sum;
}

int super_digit(string n, int k) {
    long s = digit_sum(n) * k;
    n = to_string(s);
    while (n.size() > 1) {
        s = digit_sum(n);
        n = to_string(s);
    }

    return n[0] - '0';
}

TEST_CASE("recursive digit sum") {
    REQUIRE(super_digit("148", 3) == 3);
    REQUIRE(super_digit("9875", 4) == 8);
    REQUIRE(super_digit("123", 3) == 9);
}
