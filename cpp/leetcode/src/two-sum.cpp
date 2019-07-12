// two sum

// https://leetcode.com/problems/two-sum/

// Given an array of integers, return indices of the two numbers such
// that they add up to a specific target.

// You may assume that each input would have exactly one solution, and
// you may not use the same element twice.

// Example:

// Given nums = [2, 7, 11, 15], target = 9,
// Because nums[0] + nums[1] = 2 + 7 = 9,
// return [0, 1].

#include <catch2/catch.hpp>

#include <unordered_map>
#include <vector>

using namespace std;

vector<int> two_sum(const vector<int>& nums, int target) {
    // value -> index
    unordered_map<int, int> seen;

    for (int i = 0; i < nums.size(); ++i) {
        auto it = seen.find(target - nums[i]);
        if (it != seen.end()) {
            return {it->second, i};
        } else {
            seen.insert({nums[i], i});
        }
    }

    return {};
}

TEST_CASE("two sum") {
    REQUIRE(two_sum({2, 7, 11, 15}, 9) == vector<int>{0, 1});
    REQUIRE(two_sum({2, 7, 11, 15}, 18) == vector<int>{1, 2});
}
