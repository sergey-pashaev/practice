// ex.9

// Given a list of integers, write a function that returns the largest
// sum of non-adjacent numbers. Numbers can be 0 or negative.

// For example, [2, 4, 6, 2, 5] should return 13, since we pick 2, 6,
// and 5. [5, 1, 1, 5] should return 10, since we pick 5 and 5.

// Follow-up: Can you do this in O(N) time and constant space?

#include <catch2/catch.hpp>

#include <algorithm>

using namespace std;

int f(const vector<int>& vi) {
    if (vi.empty()) return 0;

    int prev_incl = vi[0];
    int prev_excl = 0;

    for (size_t i = 1; i < vi.size(); ++i) {
        // incl - max sum of vi[0 ... i - 1]
        // excl - max sum of vi[0 ... i - 2]

        // incl is either prev_incl (max sum w/o current element)
        // or prev_excl (max sum w/o previous element but w/ current)
        int incl = max(prev_incl, prev_excl + vi[i]);

        // excl is prev_incl (max sum w/o current element)
        int excl = prev_incl;

        prev_incl = incl;
        prev_excl = excl;
    }

    return max(prev_incl, prev_excl);
}

TEST_CASE("ex.9") {
    REQUIRE(f({2, 4, 6, 2, 5}) == 13);
    REQUIRE(f({5, 1, 1, 5}) == 10);
    REQUIRE(f({5, 1}) == 5);
    REQUIRE(f({5}) == 5);
    REQUIRE(f({}) == 0);
}
