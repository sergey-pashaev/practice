// ex.2

// Given an array of integers, return a new array such that each
// element at index i of the new array is the product of all the
// numbers in the original array except the one at i.

// For example, if our input was [1, 2, 3, 4, 5], the expected output
// would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the
// expected output would be [2, 3, 6].

// Follow-up: what if you can't use division?

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

// O(2*n)
vector<int> naive(const vector<int>& vi) {
    auto ret = vi;
    // TODO: case of null in vi
    int prod = 1;
    for (int v : ret) {
        prod *= v;
    }

    for (int& v : ret) {
        v = prod / v;
    }

    return ret;
}

// O(3*n) w/o division + 2*n memory
vector<int> no_division(const vector<int>& vi) {
    vector<int> ret(vi.size(), 1);
    vector<int> l(vi.size(), 1);
    vector<int> r(vi.size(), 1);

    // l[i] = product(vi[0]..vi[i - 1])
    for (int i = 1; i < l.size(); ++i) {
        l[i] = vi[i - 1] * l[i - 1];
    }

    // r[i] = product(vi[i + 1]..vi[n])
    for (int i = r.size() - 2; i >= 0; --i) {
        r[i] = vi[i + 1] * r[i + 1];
    }

    for (int i = 0; i < ret.size(); ++i) {
        ret[i] = l[i] * r[i];
    }

    return ret;
}

// O(n) w/o division
vector<int> no_division_2(const vector<int>& vi) {
    vector<int> prod(vi.size(), 1);

    const int n = vi.size();

    // t holds products of vi[0]..v[i-1]
    int t = 1;
    for (int i = 0; i < n; ++i) {
        prod[i] = t;
        t *= vi[i];
    }

    // t holds products of v[i+1]..v[n-1]
    t = 1;
    for (int i = n - 1; i >= 0; --i) {
        prod[i] *= t; // products(vi[0]..v[i-1]) *
                      // products(vi[i+1]..v[n-1])
        t *= vi[i];
    }

    return prod;
}

struct test {
    vector<int> in;
    vector<int> out;
};

TEST_CASE("ex.2") {
    vector<test> tests = {
        {{1, 2, 3, 4, 5}, {120, 60, 40, 30, 24}},
        {{3, 2, 1}, {2, 3, 6}},
    };

    for (auto& t : tests) {
        REQUIRE(naive(t.in) == t.out);
        REQUIRE(no_division(t.in) == t.out);
        REQUIRE(no_division_2(t.in) == t.out);
    }
}
