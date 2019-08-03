// excel sheet column number

// https://leetcode.com/problems/excel-sheet-column-number/

#include <catch2/catch.hpp>

#include <string>

using namespace std;

int title_to_number(const string& s) {
    int res = 0;
    for (char c : s) {
        int d = c - 'A' + 1;
        res = res * 26 + d;
    }
    return res;
}

TEST_CASE("excel sheet column number") {
    REQUIRE(title_to_number("A") == 1);
    REQUIRE(title_to_number("AB") == 28);
    REQUIRE(title_to_number("ZY") == 701);
}
