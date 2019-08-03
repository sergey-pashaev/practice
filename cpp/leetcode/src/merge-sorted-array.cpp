// merge sorted array

// https://leetcode.com/problems/merge-sorted-array/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int out = n + m - 1;
    int i = n - 1;
    int j = m - 1;

    while (i >= 0 && j >= 0) {
        if (nums2[i] > nums1[j]) {
            nums1[out--] = nums2[i--];
        } else {
            nums1[out--] = nums1[j--];
        }
    }

    while (j >= 0) {
        nums1[out--] = nums1[j--];
    }

    while (i >= 0) {
        nums1[out--] = nums2[i--];
    }
}

TEST_CASE("merge sorted array") {
    vector<int> v1 = {1, 2, 3, 0, 0, 0};
    vector<int> v2 = {2, 5, 6};

    merge(v1, 3, v2, 3);

    REQUIRE(v1 == vector<int>{1, 2, 2, 3, 5, 6});
}
