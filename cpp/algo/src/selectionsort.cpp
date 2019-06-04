#include <catch2/catch.hpp>

#include <vector>

#include "selectionsort.h"
#include "utils.h"

void test_selectionsort(std::vector<int>& v) { psv::selectionsort(v); }

TEST_CASE("selectionsort") {
    std::vector<std::size_t> sizes = {
        {0, 1, 2, 3, 255, 256, 1000, 10000, 100000}};
    for (const std::size_t size : sizes) {
        REQUIRE(psv::is_sorted(size, test_selectionsort));
    }
}
