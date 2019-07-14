// longest common prefix

// https://leetcode.com/problems/longest-common-prefix/

// Write a function to find the longest common prefix string amongst
// an array of strings.

// If there is no common prefix, return an empty string "".

// Example 1:

// Input: ["flower","flow","flight"]
// Output: "fl"
// Example 2:

// Input: ["dog","racecar","car"]
// Output: ""
// Explanation: There is no common prefix among the input strings.
// Note:

// All given inputs are in lowercase letters a-z.

#include <catch2/catch.hpp>

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// vertical scanning approach

bool same_char(const vector<string>& vs, size_t i) {
    const int n = vs.size();
    for (int j = 0; j < n; ++j) {
        if (i >= vs[j].size()) return false;

        char c = vs[0][i];
        if (c != vs[j][i]) {
            return false;
        }
    }
    return true;
}

string lcs(const vector<string>& vs) {
    if (vs.empty()) return {};

    size_t i = 0;
    while (same_char(vs, i)) {
        ++i;
    }

    return vs[0].substr(0, i);
}

// divide & conquer approach

string common_prefix(const string& s1, const string& s2) {
    int n = min(s1.size(), s2.size());
    for (int i = 0; i < n; ++i) {
        if (s1[i] != s2[i]) {
            return s1.substr(0, i);
        }
    }

    return s1.substr(0, n);
}

string lcs_dc(const vector<string>& vs, int l, int r) {
    if (l == r) {
        return vs[l];
    } else {
        int mid = (l + r) / 2;
        string lcs_l = lcs_dc(vs, l, mid);
        string lcs_r = lcs_dc(vs, mid + 1, r);
        return common_prefix(lcs_l, lcs_r);
    }
}

string lcs_dc(const vector<string>& vs) {
    if (vs.empty()) return {};
    return lcs_dc(vs, 0, vs.size() - 1);
}

TEST_CASE("common prefix") {
    REQUIRE(common_prefix("abc", "ab") == "ab");
    REQUIRE(common_prefix("abc", "ad") == "a");
    REQUIRE(common_prefix("abc", "da") == "");
}

TEST_CASE("longest common prefix (vertical scanning)") {
    REQUIRE(lcs({}) == "");
    REQUIRE(lcs({"flower", "flow", "flight"}) == "fl");
    REQUIRE(lcs({"dog", "racecar", "car"}) == "");
}

TEST_CASE("longest common prefix (divide & conquer)") {
    REQUIRE(lcs_dc({}) == "");
    REQUIRE(lcs_dc({"flower", "flow", "flight"}) == "fl");
    REQUIRE(lcs_dc({"dog", "racecar", "car"}) == "");
}
