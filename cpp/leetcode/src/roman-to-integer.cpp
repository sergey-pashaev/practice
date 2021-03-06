// roman to integer

// https://leetcode.com/problems/roman-to-integer/

// Roman numerals are represented by seven different symbols: I, V, X, L, C, D
// and M.

// Symbol       Value
// I             1
// V             5
// X             10
// L             50
// C             100
// D             500
// M             1000

// For example, two is written as II in Roman numeral, just two one's
// added together. Twelve is written as, XII, which is simply X +
// II. The number twenty seven is written as XXVII, which is XX + V +
// II.

// Roman numerals are usually written largest to smallest from left to
// right. However, the numeral for four is not IIII. Instead, the
// number four is written as IV. Because the one is before the five we
// subtract it making four. The same principle applies to the number
// nine, which is written as IX. There are six instances where
// subtraction is used:

// I can be placed before V (5) and X (10) to make 4 and 9.
// X can be placed before L (50) and C (100) to make 40 and 90.
// C can be placed before D (500) and M (1000) to make 400 and 900.

// Given a roman numeral, convert it to an integer. Input is guaranteed to be
// within the range from 1 to 3999.

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int roman_to_int2(string s) {
    int val[26] = {};
    val['I' - 'A'] = 1;
    val['V' - 'A'] = 5;
    val['X' - 'A'] = 10;
    val['L' - 'A'] = 50;
    val['C' - 'A'] = 100;
    val['D' - 'A'] = 500;
    val['M' - 'A'] = 1000;

    const int n = s.size();
    int v = 0;

    vector<int> ints(n, 0);
    for (int i = 0; i < n; ++i) {
        ints[i] = val[static_cast<int>(s[i] - 'A')];
    }

    for (int i = 0; i < n - 1; ++i) {
        if (ints[i] < ints[i + 1]) {
            // IV, IX, XL, XC, CD, DM
            ints[i] = -ints[i];
        }
        v += ints[i];
    }

    v += ints[n - 1];
    return v;
}

int roman_to_int(string s) {
    const int n = s.size();
    int v = 0;
    for (int i = 0; i < n; ++i) {
        char curr = s[i];
        char next = i + 1 < n ? s[i + 1] : 0;
        if (curr == 'I') {
            if (next) {
                if (next == 'X') {
                    v += 9;
                    ++i;
                } else if (next == 'V') {
                    v += 4;
                    ++i;
                } else {
                    ++v;
                }
            } else {
                ++v;
            }
        } else if (curr == 'X') {
            if (next) {
                if (next == 'L') {
                    v += 40;
                    ++i;
                } else if (next == 'C') {
                    v += 90;
                    ++i;
                } else {
                    v += 10;
                }
            } else {
                v += 10;
            }
        } else if (curr == 'C') {
            if (next) {
                if (next == 'D') {
                    v += 400;
                    ++i;
                } else if (next == 'M') {
                    v += 900;
                    ++i;
                } else {
                    v += 100;
                }
            } else {
                v += 100;
            }
        } else if (curr == 'V') {
            v += 5;
        } else if (curr == 'L') {
            v += 50;
        } else if (curr == 'D') {
            v += 500;
        } else if (curr == 'M') {
            v += 1000;
        }
    }

    return v;
}

TEST_CASE("roman to integer") {
    REQUIRE(roman_to_int2("I") == 1);
    REQUIRE(roman_to_int2("II") == 2);
    REQUIRE(roman_to_int2("III") == 3);
    REQUIRE(roman_to_int2("IV") == 4);
    REQUIRE(roman_to_int2("V") == 5);
    REQUIRE(roman_to_int2("VI") == 6);
    REQUIRE(roman_to_int2("IX") == 9);
    REQUIRE(roman_to_int2("X") == 10);
    REQUIRE(roman_to_int2("XI") == 11);
    REQUIRE(roman_to_int2("XII") == 12);
    REQUIRE(roman_to_int2("LVIII") == 58);
    REQUIRE(roman_to_int2("MCMXCIV") == 1994);
}
