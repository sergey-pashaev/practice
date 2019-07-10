// jumping on the clouds

// Emma is playing a new mobile game that starts with consecutively
// numbered clouds. Some of the clouds are thunderheads and others are
// cumulus. She can jump on any cumulus cloud having a number that is
// equal to the number of the current cloud plus 1 or 2. She must avoid
// the thunderheads. Determine the minimum number of jumps it will
// take Emma to jump from her starting postion to the last cloud. It
// is always possible to win the game.

// For each game, Emma will get an array of clouds numbered 0 if they
// are safe or 1 if they must be avoided. For example, c = [0, 1, 0, 0, 0, 1, 0]
// indexed from 0 ... 6. The number on each cloud is its index in the list so
// she must avoid the clouds at indexes 1 and 5. She could follow the following
// two paths: 0 -> 2 -> 4 -> 6 or 0 -> 2 -> 3 -> 4 -> 6. The first path takes 3
// jumps while the second takes 4.

// Function Description

// Complete the jumpingOnClouds function in the editor below. It
// should return the minimum number of jumps required, as an integer.

// jumpingOnClouds has the following parameter(s):

// c: an array of binary integers

#include <catch2/catch.hpp>

#include <cassert>
#include <vector>

using namespace std;

int jumps(const vector<int>& path) {
    assert(path.size() > 1);
    assert(path.front() == 0);
    assert(path.back() == 0);

    int jumps = 0;
    int n = path.size();
    for (int i = 0; i < n - 1;) {
        if (i + 2 < n && path[i + 2] == 0) {
            // try long jump at first
            i += 2;
            ++jumps;
        } else if (i + 1 < n && path[i + 1] == 0) {
            // short jump at second
            ++i;
            ++jumps;
        } else {
            return -1;
        }
    }

    return jumps;
}

TEST_CASE("jumping on the clouds") {
    REQUIRE(jumps({0, 0, 1, 0, 0, 1, 0}) == 4);
    REQUIRE(jumps({0, 0, 0, 0, 1, 0}) == 3);
    REQUIRE(jumps({0, 0}) == 1);
    REQUIRE(jumps({0, 0, 0}) == 1);
}
