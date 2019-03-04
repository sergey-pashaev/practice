#include <catch.hpp>

#include <algorithm>
#include <random>
#include <vector>

#include "bubblesort.h"
#include "utils.h"

void test_bubblesort(std::vector<int>& v) { psv::bubblesort<int>(v); }

TEST_CASE("bubblesort") {
    std::vector<std::size_t> sizes = {{0, 1, 2, 3, 255, 256}};
    for (const std::size_t size : sizes) {
        REQUIRE(psv::is_sorted(size, test_bubblesort));
    }
}
