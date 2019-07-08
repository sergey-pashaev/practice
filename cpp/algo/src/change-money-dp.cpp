// dynamic programming example

// Coin change question: You are given n types of coin denominations
// of values V1 < V2 < ... < Vn (all integers). Assume v(1) = 1, so
// you can always make change for any amount of money M. Give an
// algorithm which gets the minimal number of coins that make change
// for an amount of money M.

#include <catch2/catch.hpp>

#include <cassert>
#include <limits>
#include <map>
#include <vector>

using namespace std;

int change(const vector<int>& values, int money, map<int, int>& memo) {
    // stop recursion
    if (money == 0) return 0;

    // check memo
    auto it = memo.find(money);
    if (it != memo.end()) {
        return it->second;
    }

    // calculate
    int min_coins = numeric_limits<int>::max();
    for (int v : values) {
        if (money - v > 0) {
            int coins = change(values, money - v, memo) + 1;
            if (coins < min_coins) {
                min_coins = coins;
            }
        }
    }

    // zero coins if can't change
    if (min_coins == numeric_limits<int>::max()) {
        min_coins = 0;
    }

    // update memo
    memo[money] = min_coins;

    return min_coins;
}

int change(const vector<int>& values, int money) {
    // init memo: money -> min coins number
    map<int, int> memo;
    for (int v : values) {
        memo[v] = 1;
    }

    return change(values, money, memo);
}

TEST_CASE("change") {
    vector<int> values = {50, 10, 5, 2, 1};

    REQUIRE(change(values, 1) == 1);
    REQUIRE(change(values, 2) == 1);
    REQUIRE(change(values, 10) == 1);
    REQUIRE(change(values, 25) == 3);
    REQUIRE(change(values, 46) == 6);
    REQUIRE(change(values, 47) == 6);
    REQUIRE(change(values, 48) == 7);
    REQUIRE(change(values, 49) == 7);
    REQUIRE(change(values, 50) == 1);
}
