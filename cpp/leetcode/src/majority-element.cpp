// majority element

// https://leetcode.com/problems/majority-element/

#include <catch2/catch.hpp>

#include <map>
#include <vector>

using namespace std;

int majority_element(const vector<int>& vi) {
    unordered_map<int, int> freq;
    for (int v : vi) {
        ++freq[v];
    }

    const int n = vi.size();
    for (auto& kv : freq) {
        if (kv.second > n / 2) {
            return kv.first;
        }
    }

    return 0;
}

TEST_CASE("majority element") {
    REQUIRE(majority_element({3, 2, 3}) == 3);
    REQUIRE(majority_element({2, 2, 1, 1, 1, 2, 2}) == 2);
}
