// zigzag conversion

// https://leetcode.com/problems/zigzag-conversion/

#include <catch2/catch.hpp>

#include <string>

using namespace std;

string convert(const string& s, int num_rows) {
    if (num_rows == 1) return s;

    int row = 1;
    int dr = 1;
    vector<string> rows(num_rows);
    for (int i = 0; i < s.size(); ++i) {
        if (row == 1) dr = 1;
        if (row == num_rows) dr = -1;
        rows[row - 1].push_back(s[i]);
        row += dr;
    }

    string ret;
    for (string& r : rows) ret += r;
    return ret;
}

TEST_CASE("zigzag conversion") {
    REQUIRE(convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
    REQUIRE(convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
}
