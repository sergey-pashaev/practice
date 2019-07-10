// new year chaos

// It's New Year's Day and everyone's in line for the Wonderland
// rollercoaster ride! There are a number of people queued up, and
// each person wears a sticker indicating their initial position in
// the queue. Initial positions increment by 1 from 1 at the front of
// the line to n at the back.

// Any person in the queue can bribe the person directly in front of
// them to swap positions. If two people swap positions, they still
// wear the same sticker denoting their original places in line. One
// person can bribe at most two others. For example, if n = 8 and
// Person 5 bribes Person 4, the queue will look like this: 1, 2, 3,
// 5, 4, 6, 7, 8.

// Fascinated by this chaotic queue, you decide you must know the
// minimum number of bribes that took place to get the queue into its
// current state!

// Function Description

// Complete the function minimumBribes in the editor below. It must
// print an integer representing the minimum number of bribes
// necessary, or Too chaotic if the line configuration is not
// possible.

// minimumBribes has the following parameter(s):

// q: an array of integers

#include <catch2/catch.hpp>

#include <cmath>
#include <vector>

using namespace std;

// ret: >= 0 - valid response
// ret: < 0 - too chaotic
int min_bribes(const vector<int>& q) {
    int bribes = 0;
    const int n = q.size();
    for (int i = 0; i < n; ++i) {
        // check if it possible for q[i] to be at i
        int offset = (q[i] - 1) - i;
        if (offset > 2) {
            return -1;
        }

        // check how many times it was bribed, by counting amount of
        // people before q[i]
        for (int j = 0; j < i; ++j) {
            if (q[j] > q[i]) {
                ++bribes;
            }
        }
    }

    return bribes;
}

TEST_CASE("new year chaos") {
    REQUIRE(min_bribes({2, 1, 5, 3, 4}) == 3);
    REQUIRE(min_bribes({2, 5, 1, 3, 4}) == -1);

    REQUIRE(min_bribes({5, 1, 2, 3, 7, 8, 6, 4}) == -1);
    REQUIRE(min_bribes({1, 2, 5, 3, 4, 7, 8, 6}) == 4);
    REQUIRE(min_bribes({1, 2, 5, 3, 7, 8, 6, 4}) == 7);
}
