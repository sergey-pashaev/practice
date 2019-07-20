// binary search

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int binary_search_i(const vector<int>& a, int v) {
    int lo = 0;
    int hi = a.size() - 1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (v < a[mid]) {
            hi = mid - 1;
        } else if (v > a[mid]) {
            lo = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int binary_search_r(const vector<int>& a, int v, int lo, int hi) {
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (v < a[mid])
            return binary_search_r(a, v, lo, mid - 1);
        else if (v > a[mid])
            return binary_search_r(a, v, mid + 1, lo);
        else if (a[mid] == v)
            return mid;
    }

    return -1;
}

TEST_CASE("binary search iterative") {
    REQUIRE(binary_search_i({1, 2, 3, 4, 5}, 0) == -1);
    REQUIRE(binary_search_i({1, 2, 3, 4, 5}, 6) == -1);
    REQUIRE(binary_search_i({1, 2, 3, 4, 5}, 1) == 0);
    REQUIRE(binary_search_i({1, 2, 3, 4, 5}, 3) == 2);
    REQUIRE(binary_search_i({1, 2, 3, 4, 5}, 5) == 4);
    REQUIRE(binary_search_i({1, 2, 3, 4}, 2) == 1);
    REQUIRE(binary_search_i({1, 2, 3, 4}, 3) == 2);
    REQUIRE(binary_search_i({1, 2}, 1) == 0);
    REQUIRE(binary_search_i({1, 2}, 2) == 1);
    REQUIRE(binary_search_i({1}, 1) == 0);
    REQUIRE(binary_search_i({1}, 2) == -1);
    REQUIRE(binary_search_i({}, 2) == -1);
}

TEST_CASE("binary search recursive") {
    REQUIRE(binary_search_i({1, 2, 3, 4, 5}, 0) == -1);
    REQUIRE(binary_search_i({1, 2, 3, 4, 5}, 6) == -1);
    REQUIRE(binary_search_i({1, 2, 3, 4, 5}, 1) == 0);
    REQUIRE(binary_search_i({1, 2, 3, 4, 5}, 3) == 2);
    REQUIRE(binary_search_i({1, 2, 3, 4, 5}, 5) == 4);
    REQUIRE(binary_search_i({1, 2, 3, 4}, 2) == 1);
    REQUIRE(binary_search_i({1, 2, 3, 4}, 3) == 2);
    REQUIRE(binary_search_i({1, 2}, 1) == 0);
    REQUIRE(binary_search_i({1, 2}, 2) == 1);
    REQUIRE(binary_search_i({1}, 1) == 0);
    REQUIRE(binary_search_i({1}, 2) == -1);
    REQUIRE(binary_search_i({}, 2) == -1);
}
