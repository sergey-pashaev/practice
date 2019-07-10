// minimum swaps 2

// You are given an unordered array consisting of consecutive integers
// [1, 2, 3, ..., n] without any duplicates. You are allowed to swap
// any two elements. You need to find the minimum number of swaps
// required to sort the array in ascending order.

// For example, given the array arr = [7, 1, 3, 2, 4, 5, 6] we perform
// the following steps:

// i   arr                     swap (indices)
// 0   [7, 1, 3, 2, 4, 5, 6]   swap (0,3)
// 1   [2, 1, 3, 7, 4, 5, 6]   swap (0,1)
// 2   [1, 2, 3, 7, 4, 5, 6]   swap (3,4)
// 3   [1, 2, 3, 4, 7, 5, 6]   swap (4,5)
// 4   [1, 2, 3, 4, 5, 7, 6]   swap (5,6)
// 5   [1, 2, 3, 4, 5, 6, 7]

// It took 5 swaps to sort the array.

// Function Description

// Complete the function minimumSwaps in the editor below. It must
// return an integer representing the minimum number of swaps to sort
// the array.

// minimumSwaps has the following parameter(s):

// arr: an unordered array of integers

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int minimum_swaps(vector<int> v) {
    int swaps = 0;

    const int n = v.size();
    for (int i = 0; i < n; ++i) {
        while ((v[i] - 1) != i) {
            swap(v[v[i] - 1], v[i]);
            ++swaps;
        }
    }

    return swaps;
}

TEST_CASE("minimum swaps 2") {
    REQUIRE(minimum_swaps({7, 1, 3, 2, 4, 5, 6}) == 5);
    REQUIRE(minimum_swaps({4, 3, 1, 2}) == 3);
    REQUIRE(minimum_swaps({2, 3, 4, 1, 5}) == 3);
    REQUIRE(minimum_swaps({1, 3, 5, 2, 4, 6, 7}) == 3);
    REQUIRE(minimum_swaps({3, 7, 6, 9, 1, 8, 10, 4, 2, 5}) == 9);
}
