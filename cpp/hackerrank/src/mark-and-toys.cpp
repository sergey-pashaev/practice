// mark and toys

// Mark and Jane are very happy after having their first child. Their
// son loves toys, so Mark wants to buy some. There are a number of
// different toys lying in front of him, tagged with their
// prices. Mark has only a certain amount to spend, and he wants to
// maximize the number of toys he buys with this money.

// Given a list of prices and an amount to spend, what is the maximum
// number of toys Mark can buy? For example, if prices = [1, 2, 3, 4]
// and Mark has k = 7 to spend, he can buy items [1, 2, 3] for 6, or
// [3, 4] for 7 units of currency. He would choose the first group of
// 3 items.

// Function Description

// Complete the function maximumToys in the editor below. It should
// return an integer representing the maximum number of toys Mark can
// purchase.

// maximumToys has the following parameter(s):

// prices: an array of integers representing toy prices
// k: an integer, Mark's budget

#include <catch2/catch.hpp>

#include <algorithm>
#include <vector>

using namespace std;

// Complete the maximumToys function below.
int maximum_toys(vector<int> prices, int k) {
    sort(prices.begin(), prices.end());

    int ret = 0;
    for (int price : prices) {
        if (k < price) {
            break;
        }

        k -= price;
        ++ret;
    }

    return ret;
}

TEST_CASE("mark and toys") {
    REQUIRE(maximum_toys({1, 12, 5, 111, 200, 1000, 10}, 50) == 4);
}
