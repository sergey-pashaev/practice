// luck balance

// Lena is preparing for an important coding competition that is
// preceded by a number of sequential preliminary contests. She
// believes in "saving luck", and wants to check her theory. Each
// contest is described by two integers, L[i] and T[i] :

// - L[i] is the amount of luck associated with a contest. If Lena
// wins the contest, her luck balance will decrease by L[i]; if she loses
// it, her luck balance will increase by L[i].

// - T[i] denotes the contest's importance rating. It's equal to 1 if
// the contest is important, and it's equal to 0 if it's unimportant.

// If Lena loses no more than k important contests, what is the
// maximum amount of luck she can have after competing in all the
// preliminary contests? This value may be negative.

// For example, k = 2 and:

// Contest      L[i]    T[i]
// 1            5       1
// 2            1       1
// 3            4       0

// If Lena loses all of the contests, her will be 5 + 1 + 4 =
// 10. Since she is allowed to lose 2 important contests, and there
// are only 2 important contests. She can lose all three contests to
// maximize her luck at 10. If k = 1, she has to win at least 1 of 2
// the important contests. She would choose to win the lowest value
// important contest worth 1. Her final luck will be 5 + 4 - 1 = 8.

// Function Description

// Complete the luckBalance function in the editor below. It should
// return an integer that represents the maximum luck balance
// achievable.

// luckBalance has the following parameter(s):

// k: the number of important contests Lena can lose

// contests: a 2D array of integers where each contains two integers
// that represent the luck balance and importance of i'th the contest.

#include <catch2/catch.hpp>

#include <algorithm>
#include <vector>

using namespace std;

int luck_balance(int k, vector<vector<int>> contests) {
    // sort by most valuable important contests at first
    sort(contests.begin(), contests.end(),
         [](const vector<int>& a, const vector<int>& b) {
             return a[1] > b[1] || (a[1] == b[1] && a[0] > b[0]);
         });

    int balance = 0;
    for (vector<int>& c : contests) {
        int l = c[0];
        int t = c[1];

        if (t == 1) {
            if (k > 0) {
                // lose important if possible
                balance += l;
                --k;
            } else {
                balance -= l;
            }
        } else {
            // lost not important
            balance += l;
        }
    }

    return balance;
}

TEST_CASE("luck balance") {
    REQUIRE(luck_balance(
                3, {{5, 1}, {2, 1}, {1, 1}, {8, 1}, {10, 0}, {5, 0}}) == 29);

    REQUIRE(luck_balance(2, {{5, 1}, {1, 1}, {4, 0}}) == 10);
    REQUIRE(luck_balance(1, {{5, 1}, {1, 1}, {4, 0}}) == 8);
}
