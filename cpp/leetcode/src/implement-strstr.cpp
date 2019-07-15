// implement strstr

// https://leetcode.com/problems/implement-strstr/

// Implement strStr().

// Return the index of the first occurrence of needle in haystack, or
// -1 if needle is not part of haystack.

// Example 1 :

// Input : haystack = "hello", needle = "ll"
// Output : 2 Example 2 :

// Input : haystack = "aaaaa", needle = "bba"
// Output : -1 Clarification :

// What should we return when needle is an empty string ? This is a
// great question to ask during an interview.

// For the purpose of this problem, we will return 0 when needle is an
// empty string .This is consistent to C 's strstr() and Java' s
// indexOf() .

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int strstr(const string& s1, const string& s2) {
    const int n1 = s1.size();
    const int n2 = s2.size();

    for (int i = 0; i <= n1 - n2; ++i) {
        int j = 0;
        for (; j < n2 && s1[i + j] == s2[j]; ++j)
            ;
        if (j == n2) return i;
    }

    return -1;
}

TEST_CASE("implement strstr") {
    REQUIRE(strstr("hello", "he") == 0);
    REQUIRE(strstr("hello", "ll") == 2);
    REQUIRE(strstr("hello", "helloo") == -1);
    REQUIRE(strstr("hello", "lo") == 3);
    REQUIRE(strstr("aaa", "ba") == -1);
    REQUIRE(strstr("aaa", "") == 0);
}
