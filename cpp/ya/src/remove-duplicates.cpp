// remove duplicates

// Дан упорядоченный по неубыванию массив целых 32-разрядных чисел. Требуется
// удалить из него все повторения.

#include <catch2/catch.hpp>

#include <limits>
#include <vector>

#include <iostream>

using namespace std;

vector<int> remove_duplicates(const vector<int>& vi) {
    int prev = numeric_limits<int>::max();
    vector<int> ret;
    for (int v : vi) {
        if (v != prev) {
            prev = v;
            ret.push_back(v);
        }
    }

    return ret;
}

TEST_CASE("remove duplicates") {
    REQUIRE(remove_duplicates({5, 4, 4, 2, 2, 1, 1}) ==
            vector<int>{5, 4, 2, 1});
    REQUIRE(remove_duplicates({1, 1, 1}) == vector<int>{1});
    REQUIRE(remove_duplicates({2, 1, 1, 1, 0}) == vector<int>{2, 1, 0});
    REQUIRE(remove_duplicates({1}) == vector<int>{1});
}
