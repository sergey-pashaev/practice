// single number

// https://leetcode.com/problems/single-number/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int single_number(const vector<int>& v) {
    int r = 0;
    for (int x : v) {
        r ^= x;
    }
    return r;
}

TEST_CASE("single number") {
    REQUIRE(single_number({2, 2, 1}) == 1);
    REQUIRE(single_number({4, 1, 2, 2, 1}) == 4);
}
