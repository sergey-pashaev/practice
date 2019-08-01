// ctci recursive staircase

// https://www.hackerrank.com/challenges/ctci-recursive-staircase/problem

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int ways(const vector<int>& hops, int step, int target, vector<int>& memo) {
    // overjmped
    if (step > target) return 0;

    // valid path
    if (step == target) return 1;

    // check memo
    if (memo[step] != -1) return memo[step];

    // calculate
    int sum = 0;
    for (int hop : hops) {
        sum += ways(hops, step + hop, target, memo);
    }

    // update memo
    memo[step] = sum;

    return sum;
}

int step_perms(int n) {
    vector<int> memo(n + 1, -1);
    return ways({1, 2, 3}, 0, n, memo);
}

TEST_CASE("ctci recursive staircase") {
    REQUIRE(step_perms(1) == 1);
    REQUIRE(step_perms(3) == 4);
    REQUIRE(step_perms(7) == 44);
}
