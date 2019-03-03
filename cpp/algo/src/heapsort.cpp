#include <catch.hpp>

#include <algorithm>
#include <iostream>
#include <random>

#include "heapsort.h"

TEST_CASE("heapsort") {
    const int size = 256;
    psv::Heap<int> h{size};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < size; ++i) {
        h.Insert(dist(gen));
    }

    std::vector<int> ret;
    for (int i = 0; i < size; ++i) {
        ret.push_back(h.ExtractRoot());
    }

    REQUIRE(std::is_sorted(ret.begin(), ret.end()));
}
