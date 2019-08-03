// pascals triangle

// https://leetcode.com/problems/pascals-triangle/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

vector<vector<int>> generate(int num_rows) {
    const int rows = num_rows;
    vector<vector<int>> a(rows);
    if (rows) {
        a[0].resize(1, 1);
        a[1].resize(2, 1);
    }
    for (int i = 2; i < rows; ++i) {
        const int count = i + 1;
        a[i].resize(count, 1);
        for (int j = 1; j < count - 1; ++j) {
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
        }
    }

    return a;
}

TEST_CASE("pascals triangle") {
    vector<vector<int>> v = {
        {1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}};

    REQUIRE(generate(5) == v);
}
