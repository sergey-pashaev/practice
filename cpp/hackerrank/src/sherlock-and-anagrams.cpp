// sherlock and anagrams

// Two strings are anagrams of each other if the letters of one string
// can be rearranged to form the other string. Given a string, find
// the number of pairs of substrings of the string that are anagrams
// of each other.

// For example s = mom, the list of all anagrammatic pairs is [m, m],
// [mo, om] at positions [[0], [2]], [[0, 1], [1,2]] respectively.

// Function Description

// Complete the function sherlockAndAnagrams in the editor below. It
// must return an integer that represents the number of anagrammatic
// pairs of substrings in s.

// sherlockAndAnagrams has the following parameter(s):

// s: a string.

#include <catch2/catch.hpp>

#include <string>
#include <unordered_map>

using namespace std;

bool is_anagram(const string& s1, const string& s2) {
    char az[26] = {};

    const size_t n = s1.size();
    for (size_t i = 0; i < n; ++i) {
        ++az[s1[i] - 'a'];
        --az[s2[i] - 'a'];
    }

    for (size_t i = 0; i < 26; ++i) {
        if (az[i] != 0) {
            return false;
        }
    }

    return true;
}

TEST_CASE("is_anagram") {
    REQUIRE(is_anagram("silent", "listen"));
    REQUIRE(is_anagram("hello", "holle"));
    REQUIRE(is_anagram("car", "rac"));

    REQUIRE(!is_anagram("car", "bac"));
    REQUIRE(!is_anagram("car", "aar"));
}

int anagrams(const string& s) {
    const size_t n = s.size();

    int count = 0;

    // try all lengths
    for (size_t len = 1; len < n; ++len) {
        // start of first substring
        for (size_t i = 0; i <= n - len; ++i) {
            // start of second substring
            for (size_t j = i + 1; j <= n - len; ++j) {
                string s1 = s.substr(i, len);
                string s2 = s.substr(j, len);
                if (is_anagram(s1, s2)) {
                    ++count;
                }
            }
        }
    }

    return count;
}

TEST_CASE("sherlock and anagrams") {
    // a a
    // ab ba
    // b b
    // abb bba
    REQUIRE(anagrams("abba") == 4);

    REQUIRE(anagrams("abcd") == 0);

    // i i
    // q q
    // ifa fai
    REQUIRE(anagrams("ifailuhkqq") == 3);

    // 6x: k k
    // 3x: kk kk
    // kkk kkk
    REQUIRE(anagrams("kkkk") == 10);

    // c c
    // d d
    // cd dc
    // cd cd
    // dc cd
    REQUIRE(anagrams("cdcd") == 5);

    REQUIRE(anagrams("ifailuhkqqhucpoltgtyovarjsnrbfpvmupwjjjfiwwhrlkpekxxnebfr"
                     "wibylcvkfealgonjkzwlyfhhkefuvgndgdnbelgruel") == 399);

    REQUIRE(anagrams("gffryqktmwocejbxfidpjfgrrkpowoxwggxaknmltjcpazgtnakcfcogz"
                     "atyskqjyorcftwxjrtgayvllutrjxpbzggjxbmxpnde") == 471);
}
