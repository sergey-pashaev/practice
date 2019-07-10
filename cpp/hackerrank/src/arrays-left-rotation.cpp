// arrays: left rotation

// A left rotation operation on an array shifts each of the array's
// elements 1 unit to the left. For example, if 2 left rotations are
// performed on array [1, 2, 3, 4, 5], then the array would become [3,
// 4, 5, 1, 2].

// Given an array a of n integers and a number, d, perform d left
// rotations on the array. Return the updated array to be printed as a
// single line of space-separated integers.

// Function Description

// Complete the function rotLeft in the editor below. It should return
// the resulting array of integers.

// rotLeft has the following parameter(s):

// An array of integers a.
// An integer d, the number of rotations.

#include <catch2/catch.hpp>

#include <cassert>
#include <vector>

using namespace std;

vector<int> lrot(const vector<int>& v, int d) {
    const std::size_t n = v.size();
    assert(d > 0);
    assert(d <= n);

    vector<int> ret(v);

    for (std::size_t i = 0; i < n; ++i) {
        ret[(i + n - d) % n] = v[i];
    }

    return ret;
}

TEST_CASE("arrays: left rotation") {
    REQUIRE(lrot({1, 2, 3, 4, 5}, 1) == vector<int>({2, 3, 4, 5, 1}));
    REQUIRE(lrot({1, 2, 3, 4, 5}, 2) == vector<int>({3, 4, 5, 1, 2}));
    REQUIRE(lrot({1, 2, 3, 4, 5}, 3) == vector<int>({4, 5, 1, 2, 3}));
    REQUIRE(lrot({1, 2, 3, 4, 5}, 4) == vector<int>({5, 1, 2, 3, 4}));
}
