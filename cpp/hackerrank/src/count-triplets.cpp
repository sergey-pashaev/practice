// count triplets

#include <catch2/catch.hpp>

#include <unordered_map>
#include <vector>

using namespace std;

long count_triplets(const vector<long>& vl, long r) {
    // progression: A, B, C
    // B = A * R
    // C = A * R * R = B * R

    // if we see B in sequence -> possible count of [A, B] parts of triplets
    unordered_map<long, long> expected_b;

    // if we see C in sequence -> possible count of [A, B, C] triplets
    unordered_map<long, long> expected_c;

    long count = 0;

    for (long v : vl) {
        // if v is expected C
        if (expected_c.count(v)) {
            count += expected_c[v];
        }

        // if v is expected B
        if (expected_b.count(v)) {
            // update expected C
            expected_c[v * r] += expected_b[v];
        }

        // v is A, so update expected B
        expected_b[v * r]++;
    }

    return count;
}

TEST_CASE("count triplets") {
    REQUIRE(count_triplets({1, 2, 2, 4}, 2) == 2);
    REQUIRE(count_triplets({1, 3, 9, 9, 27, 81}, 3) == 6);
    REQUIRE(count_triplets({1, 5, 5, 25, 125}, 5) == 4);
    REQUIRE(count_triplets({1, 1, 1, 1, 1}, 1) == 10);
    REQUIRE(count_triplets({1, 2, 1, 2, 4}, 2) == 3);
}
