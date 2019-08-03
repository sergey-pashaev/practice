// rotate array

// https://leetcode.com/problems/rotate-array/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

// O(1) space
void rotate(vector<int>& v, int k) {
    const int n = v.size();
    k = k % n;
    int swaps = 0;
    for (int beg = 0; swaps < n; ++beg) {
        int curr = beg;
        int prev = v[beg];

        do {
            int next = (curr + k) % n;
            int t = v[next];
            v[next] = prev;
            prev = t;
            curr = next;
            ++swaps;
        } while (beg != curr);
    }
}

#if 0
// O(n) space
void rotate(vector<int>& nums, int k) {
    vector<int> v(nums);
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        v[(n + i + k) % n] = nums[i];
    }
    swap(nums, v);
}
#endif

TEST_CASE("rotate array") {
    vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
    rotate(v1, 3);
    REQUIRE(v1 == vector<int>{5, 6, 7, 1, 2, 3, 4});

    vector<int> v2 = {-1, -100, 3, 99};
    rotate(v2, 2);
    REQUIRE(v2 == vector<int>{3, 99, -1, -100});
}
