#include <catch.hpp>

#include <algorithm>
#include <random>
#include <vector>

#include "mergesort.h"

TEST_CASE("mergesort") {
    const int size = 256;
    std::vector<int> v;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < size; ++i) {
        v.push_back(dist(gen));
    }

    psv::mergesort(v, 0, v.size() - 1);

    REQUIRE(std::is_sorted(v.begin(), v.end()));
}
