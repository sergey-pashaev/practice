// 2d array - ds

// Given a 6x6 2D Array, arr:

// 1 1 1 0 0 0
// 0 1 0 0 0 0
// 1 1 1 0 0 0
// 0 0 0 0 0 0
// 0 0 0 0 0 0
// 0 0 0 0 0 0

// We define an hourglass in A to be a subset of values with indices
// falling in this pattern in 's graphical representation:

// a b c
//   d
// e f g

// There are 16 hourglasses in arr, and an hourglass sum is the sum of
// an hourglass' values. Calculate the hourglass sum for every
// hourglass in , then print the maximum hourglass sum.

// For example, given the 2D array:

// -9 -9 -9  1 1 1
//  0 -9  0  4 3 2
// -9 -9 -9  1 2 3
//  0  0  8  6 6 0
//  0  0  0 -2 0 0
//  0  0  1  2 4 0

// We calculate the following 16 hourglass values:

// -63, -34, -9, 12,
// -10, 0, 28, 23,
// -27, -11, -2, 10,
// 9, 17, 25, 18

// Our highest hourglass value is 28 from the hourglass:

// 0 4 3
//   1
// 8 6 6

// Function Description

// Complete the function hourglassSum in the editor below. It should
// return an integer, the maximum hourglass sum in the array.

// hourglassSum has the following parameter(s):

// arr: an array of integers

#include <catch2/catch.hpp>

#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

int hourglass_sum(const vector<vector<int>>& v, int i, int j) {
    // clang-format off
    return v[i + 0][j + 0] + v[i + 0][j + 1] + v[i + 0][j + 2]
         + v[i + 1][j + 1]
         + v[i + 2][j + 0] + v[i + 2][j + 1] + v[i + 2][j + 2];
    // clang-format on
}

int max_sum(const vector<vector<int>>& arr) {
    int sum = numeric_limits<int>::min();
    const int sz = arr.size();
    for (int i = 0; i < sz - 2; ++i) {
        for (int j = 0; j < sz - 2; ++j) {
            sum = max(sum, hourglass_sum(arr, i, j));
        }
    }

    return sum;
}

TEST_CASE("hourglass_sum") {
    vector<vector<int>> t1 = {{0, 4, 3}, {1, 1, 1}, {8, 6, 6}};
    REQUIRE(hourglass_sum(t1, 0, 0) == 28);
}

TEST_CASE("max_sum") {
    vector<vector<int>> t1 = {
        // clang-format off
        {1, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0},
        {0, 0, 2, 4, 4, 0},
        {0, 0, 0, 2, 0, 0},
        {0, 0, 1, 2, 4, 0},
        // clang-format on
    };

    // 2 4 4
    //   2
    // 1 2 4
    REQUIRE(max_sum(t1) == 19);
}
