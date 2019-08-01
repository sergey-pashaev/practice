// angry children

// https://www.hackerrank.com/challenges/angry-children/problem

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int max_min(int k, vector<int> arr) {
    sort(arr.begin(), arr.end());

    int n = arr.size();
    int ret = numeric_limits<int>::max();
    for (int i = 0; i < n - k + 1; ++i) {
        int diff = arr[i + k - 1] - arr[i];
        ret = min(ret, diff);
    }

    return ret;
}

TEST_CASE("angry children") {
    REQUIRE(max_min(3, {10, 100, 300, 200, 1000, 20, 30}) == 20);
    REQUIRE(max_min(4, {1, 2, 3, 4, 10, 20, 30, 40, 100, 200}) == 3);
    REQUIRE(max_min(2, {1, 2, 1, 2, 1}) == 0);
}
