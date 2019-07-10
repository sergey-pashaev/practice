// repeated string

// Lilah has a string, s, of lowercase English letters that she
// repeated infinitely many times.

// Given an integer, n, find and print the number of letter a's in the
// first n letters of Lilah's infinite string.

// For example, if the string s = 'abcac' and and n = 10, the
// substring we consider is 'abcacabcac', the 10 first characters of
// her infinite string. There are 4 occurrences of a in the substring.

// Function Description

// Complete the repeatedString function in the editor below. It should
// return an integer representing the number of occurrences of a in
// the prefix of length n in the infinitely repeating string.

// repeatedString has the following parameter(s):

// s: a string to repeat
// n: the number of characters to consider

#include <catch2/catch.hpp>

#include <string>

using namespace std;

long occur(char c, const std::string& s, long n) {
    const long sz = s.size();
    const long parts = n / sz;
    const long tail = n % sz;

    long occur_whole = 0;
    long occur_tail = 0;
    for (long i = 0; i < sz; ++i) {
        // count occurences in whole part
        if (s[i] == c) {
            ++occur_whole;
            if (i < tail) {
                // count occurences in tail part
                ++occur_tail;
            }
        }
    }

    return parts * occur_whole + occur_tail;
}

TEST_CASE("repeated string") {
    REQUIRE(occur('a', "aba", 10) == 7);
    REQUIRE(occur('a', "a", 1000000000000L) == 1000000000000L);
}
