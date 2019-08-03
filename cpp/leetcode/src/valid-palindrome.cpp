// valid palindrome

// https://leetcode.com/problems/valid-palindrome/

#include <catch2/catch.hpp>

#include <cctype>
#include <string>

using namespace std;

bool is_palindrome(const string& s) {
    for (int l = 0, r = s.size() - 1; l < r; ++l, --r) {
        while (l < r && !isalnum(s[l])) ++l;
        while (l < r && !isalnum(s[r])) --r;
        if (tolower(s[l]) != tolower(s[r])) return false;
    }

    return true;
}

TEST_CASE("valid palindrome") {
    REQUIRE(is_palindrome("A man, a plan, a canal: Panama"));
    REQUIRE(!is_palindrome("race a car"));
}
