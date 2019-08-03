// house robber

// https://leetcode.com/problems/house-robber/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int rob(const vector<int>& nums) {
    int incl = 0;
    int excl = 0;

    for (int v : nums) {
        int prev_incl = incl;
        incl = v + excl;
        excl = max(excl, prev_incl);
    }

    return max(incl, excl);
}

TEST_CASE("house robber") {
    REQUIRE(rob({1, 2, 3, 1}) == 4);
    REQUIRE(rob({2, 7, 9, 3, 1}) == 12);
}
