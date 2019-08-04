// 3sum

// https://leetcode.com/problems/3sum/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

vector<vector<int>> three_sum(vector<int> nums) {
    vector<vector<int>> ret;
    const int n = nums.size();
    if (n < 3) return {};
    sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 2; ++i) {
        // eliminate duplicates
        if (i > 0 && (nums[i - 1] == nums[i])) continue;

        int v = nums[i];
        int l = i + 1;
        int r = n - 1;
        int target = -v;

        while (l < r) {
            int sum = nums[l] + nums[r];
            if (sum == target) {
                ret.push_back({v, nums[l], nums[r]});

                // eliminate duplicates
                while (l < r && nums[l] == nums[l + 1]) ++l;
                while (l < r && nums[r] == nums[r - 1]) --r;

                ++l;
                --r;
            } else if (sum < target) {
                ++l;
            } else {
                --r;
            }
        }
    }

    return ret;
}

TEST_CASE("3sum") {
    REQUIRE(three_sum({-1, 0, 1, 2, -1, -4}) ==
            vector<vector<int>>{{-1, -1, 2}, {-1, 0, 1}});
}
