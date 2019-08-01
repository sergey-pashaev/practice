// greedy florist

// https://www.hackerrank.com/challenges/greedy-florist/problem

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int min_cost(int k, vector<int> costs) {
    vector<int> bought(k, 0);

    // sort in descending order
    sort(costs.begin(), costs.end(), greater<int>());

    int total = 0;
    for (int c : costs) {
        // find person who bought min number of flowers
        int min = 0;
        for (int i = 0; i < k; ++i) {
            if (bought[i] < bought[min]) min = i;
        }

        // buy
        total += c * (1 + bought[min]);
        ++bought[min];
    }

    return total;
}

TEST_CASE("greedy florist") {
    REQUIRE(min_cost(3, {1, 3, 5, 7, 9}) == 29);
    REQUIRE(min_cost(2, {2, 5, 6}) == 15);
    REQUIRE(min_cost(3, {2, 5, 6}) == 13);
}
