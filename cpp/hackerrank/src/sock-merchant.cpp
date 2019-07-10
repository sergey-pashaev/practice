// sock merchant

// John works at a clothing store. He has a large pile of socks that
// he must pair by color for sale. Given an array of integers
// representing the color of each sock, determine how many pairs of
// socks with matching colors there are.

// For example, there are n = 7 socks with colors ar = [1, 2, 1, 2, 1,
// 3, 2]. There is one pair of color 1 and one of color 2. There are
// three odd socks left, one of each color. The number of pairs is 2.

// Function Description

// Complete the sockMerchant function in the editor below. It must
// return an integer representing the number of matching pairs of
// socks that are available.

// sockMerchant has the following parameter(s):

// n: the number of socks in the pile
// ar: the colors of each sock

#include <catch2/catch.hpp>

#include <map>
#include <vector>

using namespace std;

int pairs_count(const vector<int>& colors) {
    map<int, int> count;

    for (int color : colors) {
        count[color]++;
    }

    int pairs = 0;
    for (auto& kv : count) {
        pairs += kv.second / 2;
    }

    return pairs;
}

TEST_CASE("sock-merchant") {
    REQUIRE(pairs_count({10, 20}) == 0);
    REQUIRE(pairs_count({10, 10}) == 1);
    REQUIRE(pairs_count({10, 10, 20}) == 1);
    REQUIRE(pairs_count({10, 20, 20, 10, 10, 30, 50, 10, 20}) == 3);
}
