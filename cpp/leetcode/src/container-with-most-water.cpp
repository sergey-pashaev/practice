// container with most water

// https://leetcode.com/problems/container-with-most-water/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int max_area(const vector<int>& h) {
    const int n = h.size();
    int ret = 0;

    int l = 0;
    int r = n - 1;
    while (l < r) {
        int space = min(h[l], h[r]) * (r - l);
        ret = max(ret, space);

        if (h[l] < h[r]) {
            ++l;
        } else {
            --r;
        }
    }

    return ret;
}

TEST_CASE("container with most water") {
    REQUIRE(max_area({1, 8, 6, 2, 5, 4, 8, 3, 7}) == 49);
}
