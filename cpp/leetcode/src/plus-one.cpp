// plus one

// https://leetcode.com/problems/plus-one/

// Given a non-empty array of digits representing a non-negative
// integer, plus one to the integer.

// The digits are stored such that the most significant digit is at
// the head of the list, and each element in the array contain a
// single digit.

// You may assume the integer does not contain any leading zero,
// except the number 0 itself.

// Example 1:
// Input: [1,2,3]
// Output: [1,2,4]
// Explanation: The array represents the integer 123.

// Example 2:
// Input: [4,3,2,1]
// Output: [4,3,2,2]
// Explanation: The array represents the integer 4321.

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

vector<int> plus_one(const vector<int>& v) {
    const int n = v.size();
    bool carry = false;
    vector<int> ret(v);
    for (int i = n - 1; i >= 0; --i) {
        ++ret[i];
        if (ret[i] > 9) {
            ret[i] = 0;
            carry = true;
        } else {
            carry = false;
            break;
        }
    }

    if (carry) {
        ret.insert(ret.begin(), 1);
    }

    return ret;
}

TEST_CASE("plus one") {
    REQUIRE(plus_one({1, 2, 3}) == vector<int>{1, 2, 4});
    REQUIRE(plus_one({4, 3, 2, 1}) == vector<int>{4, 3, 2, 2});
    REQUIRE(plus_one({1, 9}) == vector<int>{2, 0});
    REQUIRE(plus_one({9}) == vector<int>{1, 0});
    REQUIRE(plus_one({9, 9, 9}) == vector<int>{1, 0, 0, 0});
    REQUIRE(plus_one({5, 9, 9}) == vector<int>{6, 0, 0});
}
