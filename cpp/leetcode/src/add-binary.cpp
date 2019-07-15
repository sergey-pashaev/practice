// add binary

// https://leetcode.com/problems/add-binary/

// Given two binary strings, return their sum (also a binary string).

// The input strings are both non-empty and contains only characters 1 or 0.

// Example 1:

// Input: a = "11", b = "1"
// Output: "100"

// Example 2:

// Input: a = "1010", b = "1011"
// Output: "10101"

#include <catch2/catch.hpp>

#include <algorithm>
#include <string>

using namespace std;

string add_binary(string a, string b) {
    const int na = a.size();
    const int nb = b.size();
    string r(max(na, nb), 0);

    int c = 0;
    for (int i = na - 1, j = nb - 1; i >= 0 || j >= 0; --i, --j) {
        int m = (i >= 0 && a[i] == '1');
        int n = (j >= 0 && b[j] == '1');

        r[max(i, j)] = '0' + ((m + n + c) & 0x1);
        c = (m + n + c) / 2;
    }

    if (c) {
        r.insert(0, 1, '1');
    }

    return r;
}

TEST_CASE("add binary") {
    REQUIRE(add_binary("11", "1") == "100");
    REQUIRE(add_binary("1010", "1011") == "10101");
    REQUIRE(add_binary("1011", "1011") == "10110");
}
