// best time to buy and sell stock II

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int max_profit(const vector<int>& p) {
    const int n = p.size();
    int profit = 0;
    for (int i = 1; i < n; ++i) {
        if (p[i] > p[i - 1]) profit += p[i] - p[i - 1];
    }
    return profit;
}

TEST_CASE("best time to buy and sell stock II") {
    REQUIRE(max_profit({7, 1, 5, 3, 6, 4}) == 7);
    REQUIRE(max_profit({1, 2, 3, 4, 5}) == 4);
    REQUIRE(max_profit({7, 6, 4, 3, 1}) == 0);
}
