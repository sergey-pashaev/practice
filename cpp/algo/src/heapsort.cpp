#include <catch2/catch.hpp>

#include <vector>

#include "heapsort.h"
#include "utils.h"

void test_heapsort(std::vector<int>& v) {
    const int size = v.size();
    psv::Heap<int> h{size};
    for (const auto& e : v) {
        h.Insert(e);
    }

    for (int i = 0; i < size; ++i) {
        v[i] = h.ExtractRoot();
    }
}

TEST_CASE("heapsort") {
    std::vector<std::size_t> sizes = {
        {0, 1, 2, 3, 255, 256, 1000, 10000}};
    for (const std::size_t size : sizes) {
        REQUIRE(psv::is_sorted(size, test_heapsort));
    }
}
