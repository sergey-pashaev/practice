// two strings

// Given two strings, determine if they share a common substring. A
// substring may be as small as one character.

// For example, the words "a", "and", "art" share the common substring
// a. The words "be" and "cat" do not share a substring.

// Function Description

// Complete the function twoStrings in the editor below. It should
// return a string, either YES or NO based on whether the strings
// share a common substring.

// twoStrings has the following parameter(s):

// s1, s2: two strings to analyze.

#include <catch2/catch.hpp>

#include <string>
#include <unordered_set>

using namespace std;

bool common_str(const string& s1, const string& s2) {
    unordered_set<char> set1(s1.begin(), s1.end());

    for (char c : s2) {
        if (set1.find(c) != set1.end()) {
            return true;
        }
    }

    return false;
}

TEST_CASE("two strings") {
    REQUIRE(common_str("hello", "world"));
    REQUIRE(!common_str("hi", "world"));
}
