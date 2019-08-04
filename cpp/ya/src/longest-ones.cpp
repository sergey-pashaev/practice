// longest ones

// Требуется найти в бинарном векторе самую длинную последовательность единиц и
// вывести её длину.

#include <catch2/catch.hpp>

#include <algorithm>
#include <vector>

using namespace std;

int longest_ones(const vector<int>& vi) {
    int curr = 0;
    int best = 0;

    for (int v : vi) {
        if (v == 1) {
            ++curr;
        } else {
            curr = 0;
        }

        best = max(curr, best);
    }

    return best;
}

TEST_CASE("longest ones") {
    REQUIRE(longest_ones({1, 1, 0, 0, 1, 1, 1}) == 3);
    REQUIRE(longest_ones({1, 1, 0, 1, 1, 0, 1}) == 2);
    REQUIRE(longest_ones({0, 1, 1, 1, 1, 1, 0, 1}) == 5);
    REQUIRE(longest_ones({1}) == 1);
    REQUIRE(longest_ones({1, 1}) == 2);
    REQUIRE(longest_ones({0}) == 0);
    REQUIRE(longest_ones({}) == 0);
}
