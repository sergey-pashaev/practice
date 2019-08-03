// jump game

// https://leetcode.com/problems/jump-game/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

bool can_jump(const vector<int>& nums) {
    const int n = nums.size();
    int prev = n - 1;
    for (int curr = n - 1; curr >= 0; --curr) {
        if (curr + nums[curr] >= prev) prev = curr;
    }
    return prev == 0;
}

TEST_CASE("jump game") {
    REQUIRE(can_jump({2, 3, 1, 1, 4}));
    REQUIRE(!can_jump({3, 2, 1, 0, 4}));
}
