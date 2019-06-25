// ex.4

// Given an array of integers, find the first missing positive integer
// in linear time and constant space. In other words, find the lowest
// positive integer that does not exist in the array. The array can
// contain duplicates and negative numbers as well.

// For example, the input [3, 4, -1, 1] should give 2. The input [1,
// 2, 0] should give 3.

// You can modify the input array in-place.

#include <catch2/catch.hpp>

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int segregate(int a[], int size) {
    int j = 0;
    for (int i = 0; i < size; ++i) {
        if (a[i] <= 0) {
            swap(a[i], a[j]);
            ++j;
        }
    }

    return j;
}

int lowest_positive_missing(int a[], int size) {
    for (int i = 0; i < size; ++i) {
        int idx = abs(a[i]) - 1;
        if (idx < size && a[idx] > 0) {
            a[idx] = -a[idx];
        }
    }

    for (int i = 0; i < size; ++i) {
        if (a[i] > 0) return i + 1;
    }

    return size + 1;
}

int lowest_positive_missing(vector<int>&& v) {
    int* a = v.data();
    int shift = segregate(a, v.size());
    return lowest_positive_missing(a + shift, v.size() - shift);
}

TEST_CASE("ex.4") {
    REQUIRE(lowest_positive_missing({3, 4, -1, 1}) == 2);
    REQUIRE(lowest_positive_missing({1, 2, 0}) == 3);
    REQUIRE(lowest_positive_missing({-1}) == 1);
    REQUIRE(lowest_positive_missing({0}) == 1);
    REQUIRE(lowest_positive_missing({1}) == 2);
    REQUIRE(lowest_positive_missing({1, 2, 4, 5}) == 3);
    REQUIRE(lowest_positive_missing({1, 2, 3, 5, 6}) == 4);
}
