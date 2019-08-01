// longest palindromic substring

// https://leetcode.com/problems/longest-palindromic-substring/solution/

#include <catch2/catch.hpp>

#include <string>

using namespace std;

int palindrome_d(const string& s, int l, int r) {
    const int n = s.size();
    while (l >= 0 && r < n && s[l] == s[r]) {
        --l;
        ++r;
    }
    return r - l - 1;
}

string lps_brute(const string& s) {
    const int n = s.size();
    int mlen = 0;
    string ret;
    for (int i = 0; i < n; ++i) {
        {
            int len = palindrome_d(s, i, i);
            if (len > mlen) {
                ret = s.substr(i - len / 2, len);
                mlen = len;
            }
        }

        if (i + 1 < n) {
            int len = palindrome_d(s, i, i + 1);
            if (len > mlen) {
                ret = s.substr(i - len / 2 + 1, len);
                mlen = len;
            }
        }
    }

    return ret;
}

string lps(const string& s) { return lps_brute(s); }

TEST_CASE("longest palindromic substring") {
    REQUIRE(lps("babad") == "bab");
    REQUIRE(lps("cbbd") == "bb");
    REQUIRE(lps("bababasa") == "babab");
}
