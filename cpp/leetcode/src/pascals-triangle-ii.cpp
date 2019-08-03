// pascals triangle II

// https://leetcode.com/problems/pascals-triangle-ii/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

vector<int> get_row(int row_idx) {
    const int rows = row_idx + 1;
    vector<int> v1(rows, 1);
    vector<int> v2(rows, 1);

    if (rows <= 2) {
        v2.resize(rows);
        return v2;
    }

    vector<int>& curr = v1;
    vector<int>& prev = v2;

    for (int i = 2; i < rows; ++i) {
        for (int j = 1; j < i; ++j) {
            curr[j] = prev[j - 1] + prev[j];
        }
        swap(curr, prev);
    }

    prev.resize(rows);
    return prev;
}

TEST_CASE("pascals triangle II") {
    REQUIRE(get_row(3) == vector<int>{1, 3, 3, 1});
}
