// alternating characters

// You are given a string containing characters A and B only. Your task is
// to change it into a string such that there are no matching adjacent
// characters. To do this, you are allowed to delete zero or more
// characters in the string.

// Your task is to find the minimum number of required deletions.

// For example, given the string s = AABAAB, remove an A at positions
// 0 and 3 to make s = ABAB in 2 deletions.

// Function Description

// Complete the alternatingCharacters function in the editor below. It
// must return an integer representing the minimum number of deletions
// to make the alternating string.

// alternatingCharacters has the following parameter(s):

// s: a string

#include <catch2/catch.hpp>

#include <string>

using namespace std;

int min_deletions(const string& s) {
    int ret = 0;
    char prev = 0;
    for (char c : s) {
        if (c == prev) {
            ++ret;
        }
        prev = c;
    }

    return ret;
}

TEST_CASE("alternating characters") {
    REQUIRE(min_deletions("AAAA") == 3);
    REQUIRE(min_deletions("BBBBB") == 4);
    REQUIRE(min_deletions("ABABABAB") == 0);
    REQUIRE(min_deletions("BABABA") == 0);
    REQUIRE(min_deletions("AAABBB") == 4);
}
