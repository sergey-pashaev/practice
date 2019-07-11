// strings making anagrams

// Alice is taking a cryptography class and finding anagrams to be
// very useful. We consider two strings to be anagrams of each other
// if the first string's letters can be rearranged to form the second
// string. In other words, both strings must contain the same exact
// letters in the same exact frequency For example, bacdc and dcbac
// are anagrams, but bacdc and dcbad are not.

// Alice decides on an encryption scheme involving two large strings
// where encryption is dependent on the minimum number of character
// deletions required to make the two strings anagrams. Can you help
// her find this number?

// Given two strings, a and b, that may or may not be of the same
// length, determine the minimum number of character deletions
// required to make a and b anagrams. Any characters can be deleted
// from either of the strings.

// For example, if a = cde and b = dcf, we can delete 'e' from string
// a and 'f' from string b so that both remaining strings are 'cd' and
// 'dc' which are anagrams.

// Function Description

// Complete the makeAnagram function in the editor below. It must
// return an integer representing the minimum total characters that
// must be deleted to make the strings anagrams.

// makeAnagram has the following parameter(s):

// a: a string
// b: a string

#include <catch2/catch.hpp>

#include <cmath>
#include <vector>

using namespace std;

int min_deletions(const string& a, const string& b) {
    // build characters frequence set
    constexpr int k_az_size = 26;
    vector<int> freq(k_az_size, 0);

    // add to count
    for (char c : a) {
        ++freq[c - 'a'];
    }

    // substract to find difference
    for (char c : b) {
        --freq[c - 'a'];
    }

    // sum all differences
    int deletions = 0;
    for (int v : freq) {
        deletions += abs(v);
    }

    return deletions;
}

TEST_CASE("strings making anagrams") {
    REQUIRE(min_deletions("cde", "abc") == 4);
    REQUIRE(min_deletions("abc", "abb") == 2);
}
