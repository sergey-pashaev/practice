// sherlock and the valid string

// Sherlock considers a string to be valid if all characters of the
// string appear the same number of times. It is also valid if he can
// remove just 1 character at 1 index in the string, and the remaining
// characters will occur the same number of times. Given a string s,
// determine if it is valid. If so, return YES, otherwise return NO.

// For example, if s = abc, it is a valid string because frequencies
// are {a:1, b:1 c:1}. So is s = abcc because we can remove one 'c'
// and have of 1 each character in the remaining string. If s = abccc
// however, the string is not valid as we can only remove 1 occurrence
// of 'c'. That would leave character frequencies of {a:1, b:1, c:2}.

// Function Description

// Complete the isValid function in the editor below. It should return
// either the string YES or the string NO.

// isValid has the following parameter(s):

// s: a string

#include <catch2/catch.hpp>

#include <limits>
#include <string>
#include <vector>

using namespace std;

bool is_valid(const string& s) {
    const int az_size = 26;
    vector<int> freq(az_size, 0);

    for (char c : s) {
        ++freq[c - 'a'];
    }

    int min = numeric_limits<int>::max();
    int max = numeric_limits<int>::min();
    freq.erase(std::remove_if(std::begin(freq), std::end(freq),
                              [](int v) { return v == 0; }),
               std::end(freq));

    for (int f : freq) {
        if (f > max) {
            max = f;
        }

        if (f < min) {
            min = f;
        }
    }

    int min_count = 0;
    int max_count = 0;

    for (int f : freq) {
        if (f == min) ++min_count;
        if (f == max) ++max_count;
    }

    if (min == max) {
        // only one freq
        return true;
    }

    if ((min_count + max_count) != freq.size()) {
        // more than two freqs
        return false;
    }

    if (min_count == 1 && min == 1) {
        // one extra char with min freq
        return true;
    } else if (max == min + 1 && max_count == 1) {
        // one extra char with max freq
        return true;
    } else {
        return false;
    }
}

TEST_CASE("sherlock and the valid string") {
    REQUIRE(is_valid("abc"));
    REQUIRE(is_valid("abcc"));
    REQUIRE(!is_valid("abccc"));

    REQUIRE(!is_valid("aabbcd"));
    REQUIRE(!is_valid("aabbccddeefghi"));
    REQUIRE(is_valid("abcdefghhgfedecba"));
}
