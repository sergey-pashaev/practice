// minimum absolute difference in an array

// Consider an array of integers, arr = [arr[0], arr[1], ...,
// arr[n-1]]. We define the absolute difference between two elements,
// a[i] and a[j] (where i != j), to be the absolute value of a[i] -
// a[j].

// Given an array of integers, find and print the minimum absolute
// difference between any two elements in the array. For example,
// given the array arr = [-2, 2, 4] we can create 3 pairs of numbers:
// [-2, 2], [-2, 4] and [2, 4]. The absolute differences for these
// pairs are |(-2) -2| = 4, |(-2) -4| = 6 and |2 - 4| = 2. The minimum
// absolute difference is 2.

// Function Description

// Complete the minimumAbsoluteDifference function in the editor
// below. It should return an integer that represents the minimum
// absolute difference between any pair of elements.

// minimumAbsoluteDifference has the following parameter(s):

// n: an integer that represents the length of arr
// arr: an array of integers

#include <catch2/catch.hpp>

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int min_diff(vector<int> arr) {
    // sort it & compare minimum(a[0], a[1]) w/ everything else
    int n = arr.size();
    std::sort(arr.begin(), arr.end());
    int ans = abs(arr[0] - arr[1]);
    for (int i = 1; i < n - 1; ++i) {
        int diff = abs(arr[i] - arr[i + 1]);
        if (diff < ans) {
            ans = diff;
        }
    }
    return ans;
}

TEST_CASE("minimum absolute difference in an array") {
    REQUIRE(min_diff({2, 2, 2}) == 0);
    REQUIRE(min_diff({-2, 2, 4}) == 2);
    REQUIRE(min_diff({3, -7, 0}) == 3);
    REQUIRE(min_diff({-59, -36, -13, 1, -53, -92, -2, -96, -54, 75}) == 1);
    REQUIRE(min_diff({1, -3, 71, 68, 17}) == 3);
}
