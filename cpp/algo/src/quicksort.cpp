#include <catch.hpp>

#include <vector>

#include "quicksort.h"
#include "utils.h"

void test_quicksort(std::vector<int>& v) { psv::quicksort(v); }

TEST_CASE("quicksort") {
    std::vector<std::size_t> sizes = {
        {0, 1, 2, 3, 255, 256, 1000, 10000, 100000}};
    for (const std::size_t size : sizes) {
        REQUIRE(psv::is_sorted(size, test_quicksort));
    }
}
