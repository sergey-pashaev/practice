// two sum II input array is sorted

// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

vector<int> two_sum(const vector<int>& v, int target) {
    const int n = v.size();
    int l = 0;
    int r = n - 1;

    while (l != r - 1) {
        int sum = v[l] + v[r];
        if (sum < target) {
            ++l;
        } else if (sum > target) {
            --r;
        } else {
            return {l + 1, r + 1};
        }
    }

    return {l + 1, r + 1};
}

TEST_CASE("two sum II input array is sorted") {
    REQUIRE(two_sum({2, 7, 11, 15}, 0) == vector<int>{1, 2});
}
