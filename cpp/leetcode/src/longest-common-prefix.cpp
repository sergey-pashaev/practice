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

#include <string>
#include <vector>

using namespace std;

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

TEST_CASE("longest common prefix") {
    REQUIRE(lcs({}) == "");
    REQUIRE(lcs({"flower", "flow", "flight"}) == "fl");
    REQUIRE(lcs({"dog", "racecar", "car"}) == "");
}
