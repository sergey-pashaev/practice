// best time to buy and sell stock

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

#include <catch2/catch.hpp>

#include <limits>
#include <vector>

using namespace std;

int max_profit(const vector<int>& pr) {
    const int n = pr.size();
    int p = 0;
    int buy = numeric_limits<int>::max();
    for (int i = 0; i < n; ++i) {
        if (pr[i] < buy) {
            buy = pr[i];
        } else if (pr[i] - buy > p) {
            p = pr[i] - buy;
        }
    }

    return p;
}

TEST_CASE("best time to buy and sell stock") {
    REQUIRE(max_profit({7, 1, 5, 3, 6, 4}) == 5);
    REQUIRE(max_profit({7, 6, 4, 3, 1}) == 0);
}
