// search insert position

// https://leetcode.com/problems/search-insert-position

// Given a sorted array and a target value, return the index if the
// target is found. If not, return the index where it would be if it
// were inserted in order.

// You may assume no duplicates in the array.

// Example 1:
// Input: [1,3,5,6], 5
// Output: 2

// Example 2:
// Input: [1,3,5,6], 2
// Output: 1

// Example 3:
// Input: [1,3,5,6], 7
// Output: 4

// Example 4:
// Input: [1,3,5,6], 0
// Output: 0

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int insert_position(const vector<int>& v, int target) {
    const int n = v.size();
    int i = 0;
    while (i < n && v[i] < target) ++i;
    return i;
}

// binary search
int insert_position_bs(const vector<int>& v, int target) {
    int lo = 0;
    int hi = v.size() - 1;

    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (target <= v[mid]) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return lo < v.size() - 1 ? lo : lo + 1;
}

TEST_CASE("search insert position") {
    REQUIRE(insert_position({1, 3, 5, 6}, 5) == 2);
    REQUIRE(insert_position({1, 3, 5, 6}, 2) == 1);
    REQUIRE(insert_position({1, 3, 5, 6}, 7) == 4);
    REQUIRE(insert_position({1, 3, 5, 6}, 0) == 0);
}

TEST_CASE("search insert position (binary search)") {
    REQUIRE(insert_position_bs({1, 3, 5, 6}, 5) == 2);
    REQUIRE(insert_position_bs({1, 3, 5, 6}, 2) == 1);
    REQUIRE(insert_position_bs({1, 3, 5, 6}, 7) == 4);
    REQUIRE(insert_position_bs({1, 3, 5, 6}, 0) == 0);
}
