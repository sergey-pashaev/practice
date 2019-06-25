// ex.1

// Given a list of numbers and a number k, return whether any two
// numbers from the list add up to k.

// For example, given [10, 15, 3, 7] and k of 17, return true since 10
// + 7 is 17.

// Bonus: Can you do this in one pass?

#include <catch2/catch.hpp>

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <vector>

using namespace std;

// O(n^2)
bool quadratic(const vector<int>& vi, int k) {
    const size_t sz = vi.size();
    for (size_t i = 0; i < sz - 1; ++i) {
        for (size_t j = i + 1; j < sz; ++j) {
            if (vi[i] + vi[j] == k) return true;
        }
    }

    return false;
}

// O(nlogn) + memory(n)
bool nlogn(const vector<int>& vi, int k) {
    assert(vi.size());
    auto v = vi;
    sort(v.begin(), v.end());

    int n1 = 0;
    int n2 = v.size() - 1;
    while (v[n1] > k) ++n1;
    while (v[n2] > k) --n2;

    while (n1 != n2) {
        if (v[n1] + v[n2] > k) {
            --n2;
        } else if (v[n1] + v[n2] < k) {
            ++n1;
        } else {
            return true;
        }
    }

    return false;
}

// O(nlogn) + memory(n)
bool nlogn_it(const vector<int>& vi, int k) {
    assert(vi.size());
    auto v = vi;
    sort(v.begin(), v.end());

    auto n1 = v.begin();
    auto n2 = v.end() - 1;
    while (*n1 > k) ++n1;
    while (*n2 > k) --n2;

    while (n1 != n2) {
        if (*n1 + *n2 > k) {
            --n2;
        } else if (*n1 + *n2 < k) {
            ++n1;
        } else {
            return true;
        }
    }

    return false;
}

// O(n) + memory(n)
bool linear(const vector<int>& vi, int k) {
    unordered_set<int> s;
    for (int v : vi) {
        if (s.find(k - v) != s.end()) return true;
        s.insert(v);
    }

    return false;
}

struct test {
    bool res;
    int k;
    vector<int> v;
};

TEST_CASE("ex.1") {
    vector<test> tests = {
        {true, 17, {10, 15, 3, 7}}, {true, 17, {1, 10, 15, 11, 2, 7}},
        {true, 17, {10, 7}},        {false, 17, {7}},
        {false, 17, {17}},          {false, 17, {1, 2}},
    };

    for (auto& t : tests) {
        REQUIRE(quadratic(t.v, t.k) == t.res);
        REQUIRE(nlogn(t.v, t.k) == t.res);
        REQUIRE(nlogn_it(t.v, t.k) == t.res);
        REQUIRE(linear(t.v, t.k) == t.res);
    }
}
