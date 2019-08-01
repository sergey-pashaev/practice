// longest substring without repeating characters

// https://leetcode.com/problems/longest-substring-without-repeating-characters/

#include <catch2/catch.hpp>

#include <map>
#include <string>

using namespace std;

int length_of_longest_substring(const string& s) {
    map<char, int> seen;
    int best = 0;
    int n = s.size();
    for (int beg = 0, end = 0; end < n; ++end) {
        char c = s[end];
        if (seen.count(c)) {
            beg = max(seen[c], beg);
        }
        best = max(best, end - beg + 1);
        seen[c] = end + 1;
    }
    return best;
}

TEST_CASE("longest substring without repeating characters") {
    REQUIRE(length_of_longest_substring("abcabcbb") == 3);
    REQUIRE(length_of_longest_substring("bbbbbb") == 1);
    REQUIRE(length_of_longest_substring("pwwkew") == 3);
}
