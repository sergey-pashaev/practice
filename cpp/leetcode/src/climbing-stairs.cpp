// climbing stairs

// https://leetcode.com/problems/climbing-stairs/solution/

// You are climbing a stair case. It takes n steps to reach to the
// top.

// Each time you can either climb 1 or 2 steps. In how many distinct
// ways can you climb to the top?

// Note: Given n will be a positive integer.

// Example 1:
// Input: 2
// Output: 2
// Explanation: There are two ways to climb to the top.
// 1. 1 step + 1 step
// 2. 2 steps

// Example 2:
// Input: 3
// Output: 3
// Explanation: There are three ways to climb to the top.
// 1. 1 step + 1 step + 1 step
// 2. 1 step + 2 steps
// 3. 2 steps + 1 step

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int paths_brute(const vector<int>& hops, int step, int target) {
    if (step > target)
        // impossible path, we overjumped target
        return 0;
    else if (step == target)
        // valid path
        return 1;
    else {
        // sum of all possible paths
        int sum = 0;
        for (int hop : hops) {
            sum += paths_brute(hops, step + hop, target);
        }
        return sum;
    }
}

int paths_brute(const vector<int>& hops, int steps) {
    return paths_brute(hops, 0, steps);
}

TEST_CASE("climbing stairs brute") {
    vector<int> hops = {1, 2};

    REQUIRE(paths_brute(hops, 0) == 1);
    REQUIRE(paths_brute(hops, 1) == 1);
    REQUIRE(paths_brute(hops, 2) == 2);
    REQUIRE(paths_brute(hops, 3) == 3);
    REQUIRE(paths_brute(hops, 4) == 5);
    REQUIRE(paths_brute(hops, 5) == 8);
    REQUIRE(paths_brute(hops, 6) == 13);
    REQUIRE(paths_brute(hops, 7) == 21);
}

int paths_memo(const vector<int>& hops, int step, int target,
               vector<int>& memo) {
    if (step > target)
        // impossible path, we overjumped target
        return 0;
    else if (step == target)
        // valid path
        return 1;
    else {
        // check memo
        if (memo[step] > 0) return memo[step];

        // calculate
        // sum of all possible paths
        int sum = 0;
        for (int hop : hops) {
            sum += paths_memo(hops, step + hop, target, memo);
        }

        // update memo
        memo[step] = sum;
        return sum;
    }
}

int paths_memo(const vector<int>& hops, int steps) {
    vector<int> memo(steps + 1, 0);
    return paths_memo(hops, 0, steps, memo);
}

TEST_CASE("climbing stairs memo") {
    vector<int> hops = {1, 2};

    REQUIRE(paths_memo(hops, 0) == 1);
    REQUIRE(paths_memo(hops, 1) == 1);
    REQUIRE(paths_memo(hops, 2) == 2);
    REQUIRE(paths_memo(hops, 3) == 3);
    REQUIRE(paths_memo(hops, 4) == 5);
    REQUIRE(paths_memo(hops, 5) == 8);
    REQUIRE(paths_memo(hops, 6) == 13);
    REQUIRE(paths_memo(hops, 7) == 21);
}
