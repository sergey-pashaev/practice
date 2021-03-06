#include <catch2/catch.hpp>

#include <vector>

#include "mergesort.h"
#include "utils.h"

void test_mergesort(std::vector<int>& v) { psv::mergesort(v); }

TEST_CASE("mergesort") {
    std::vector<std::size_t> sizes = {
        {0, 1, 2, 3, 255, 256, 1000, 10000}};
    for (const std::size_t size : sizes) {
        REQUIRE(psv::is_sorted(size, test_mergesort));
    }
}
