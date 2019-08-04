// spiral matrix

// https://leetcode.com/problems/spiral-matrix/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

vector<int> spiral_order(const vector<vector<int>>& m) {
    int rows = m.size();
    if (!rows) return {};
    int cols = m[0].size();

    int r1 = 0;
    int r2 = rows - 1;
    int c1 = 0;
    int c2 = cols - 1;

    vector<int> ret;
    ret.reserve(rows * cols);
    while (r1 <= r2 && c1 <= c2) {
        for (int c = c1; c <= c2; ++c) ret.push_back(m[r1][c]);
        for (int r = r1 + 1; r <= r2; ++r) ret.push_back(m[r][c2]);
        if (r1 < r2 && c1 < c2) {
            for (int c = c2 - 1; c >= c1 + 1; --c) ret.push_back(m[r2][c]);
            for (int r = r2; r >= r1 + 1; --r) ret.push_back(m[r][c1]);
        }

        ++r1;
        --r2;
        ++c1;
        --c2;
    }

    return ret;
}

TEST_CASE("spiral matrix") {
    vector<vector<int>> v1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    REQUIRE(spiral_order(v1) == vector<int>{1, 2, 3, 6, 9, 8, 7, 4, 5});
    vector<vector<int>> v2 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    REQUIRE(spiral_order(v2) ==
            vector<int>{1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7});
}
