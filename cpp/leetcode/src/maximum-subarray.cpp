// maximum subarray

// https://leetcode.com/problems/maximum-subarray/

// Given an integer array nums, find the contiguous subarray
// (containing at least one number) which has the largest sum and
// return its sum.

// Example:

// Input: [-2,1,-3,4,-1,2,1,-5,4],
// Output: 6

// Explanation: [4,-1,2,1] has the largest sum = 6.

// Follow up: If you have figured out the O(n) solution, try coding
// another solution using the divide and conquer approach, which is
// more subtle.

#include <catch2/catch.hpp>

#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

int max_subarray_brute(const vector<int>& a) {
    int max = numeric_limits<int>::min();
    const int n = a.size();
    for (int len = 0; len < n; ++len) {
        for (int i = 0; i < n - len; ++i) {
            int sum = 0;
            for (int j = 0; j <= len; ++j) {
                sum += a[i + j];
            }
            if (sum > max) {
                max = sum;
            }
        }
    }
    return max;
}

int max_subarray(const vector<int>& a) {
    int sum = a[0];
    int gsum = a[0];
    int n = a.size();
    for (int i = 1; i < n; ++i) {
        if (a[i] > sum + a[i]) {
            sum = a[i];
        } else {
            sum += a[i];
        }

        gsum = max(sum, gsum);
    }

    return gsum;
}

TEST_CASE("maximum subarray") {
    REQUIRE(max_subarray({-2, 1, -3, 4, -1, 2, 1, -5, 4}) == 6);
    REQUIRE(max_subarray({1}) == 1);
    REQUIRE(max_subarray({1, 2}) == 3);
    REQUIRE(max_subarray({1, -3, 2, 1, -1}) == 3);
}
