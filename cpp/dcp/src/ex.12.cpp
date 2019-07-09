// ex.12

// There exists a staircase with N steps, and you can climb up either
// 1 or 2 steps at a time. Given N, write a function that returns the
// number of unique ways you can climb the staircase. The order of the
// steps matters.

// For example, if N is 4, then there are 5 unique ways:

// 1, 1, 1, 1
// 2, 1, 1
// 1, 2, 1
// 1, 1, 2
// 2, 2

// What if, instead of being able to climb 1 or 2 steps at a time, you
// could climb any number from a set of positive integers X?  For
// example, if X = {1, 3, 5}, you could climb 1, 3, or 5 steps at a
// time.

#include <catch2/catch.hpp>

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

// TODO: use memoization
int ways(const vector<int>& hops, int steps) {
    if (steps < 0)
        return 0;
    else if (steps == 0)
        return 1;
    else {
        auto it = find(hops.begin(), hops.end(), steps);
        int sum = it != hops.end() ? 1 : 0;
        for (int hop : hops) {
            if (hop < steps) {
                sum += ways(hops, steps - hop);
            }
        }
        return sum;
    }
}

TEST_CASE("ex.12") {
    vector<int> hops = {1, 2};

    REQUIRE(ways(hops, 0) == 1);
    REQUIRE(ways(hops, 1) == 1);
    REQUIRE(ways(hops, 2) == 2);
    REQUIRE(ways(hops, 3) == 3);
    REQUIRE(ways(hops, 4) == 5);
    REQUIRE(ways(hops, 5) == 8);
    REQUIRE(ways(hops, 6) == 13);
    REQUIRE(ways(hops, 7) == 21);
}
