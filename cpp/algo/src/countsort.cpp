#include <catch2/catch.hpp>

#include <vector>

#include "utils.h"

using namespace std;

constexpr int N = 100;  // algorithm works only for 0 <= i <= N

void countsort(vector<int>& vi) {
    vector<int> count(N + 1, 0);
    for (int v : vi) {
        ++count[v];
    }

    int out = 0;
    for (int i = 0; i <= N + 1; ++i) {
        while (count[i] > 0) {
            vi[out] = i;
            --count[i];
            ++out;
        }
    }
}

TEST_CASE("countsort") {
    std::vector<std::size_t> sizes = {
        {0, 1, 2, 3, 255, 256, 1'000, 10'000, 100'000, 1'000'000}};
    for (const std::size_t size : sizes) {
        REQUIRE(psv::is_sorted(size, countsort, N));
    }
}
