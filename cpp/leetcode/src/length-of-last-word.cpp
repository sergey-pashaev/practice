// length of last word

// https://leetcode.com/problems/length-of-last-word/

// Given a string s consists of upper/lower-case alphabets and empty
// space characters ' ', return the length of last word in the string.

// If the last word does not exist, return 0.

// Note: A word is defined as a character sequence consists of
// non-space characters only.

// Example:
// Input: "Hello World"
// Output: 5

#include <catch2/catch.hpp>

#include <string>

using namespace std;

int length_of_last_word(const string& s) {
    const int n = s.size();
    int ret = 0;
    int i = n - 1;

    // skip trailing spaces
    while (i >= 0 && s[i] == ' ') --i;

    // count word len
    while (i >= 0 && s[i] != ' ') {
        --i;
        ++ret;
    }

    return ret;
}

TEST_CASE("length of last word") {
    REQUIRE(length_of_last_word("hello") == 5);
    REQUIRE(length_of_last_word("hello ") == 5);
    REQUIRE(length_of_last_word("last word") == 4);
    REQUIRE(length_of_last_word("last word  ") == 4);
    REQUIRE(length_of_last_word("") == 0);
}
