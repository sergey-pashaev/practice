// kangaroo

// https://www.hackerrank.com/challenges/kangaroo/problem

#include <catch2/catch.hpp>

using namespace std;

bool kangaroo(int x1, int v1, int x2, int v2) {
    int dv = max(v1, v2) - min(v1, v2);
    int dx = max(x1, x2) - min(x1, x2);

    if (x1 > x2) {
        if (v1 >= v2) return false;
    } else {
        if (v2 >= v1) return false;
    }

    return dx % dv == 0;
}

TEST_CASE("kangaroo") {
    REQUIRE(kangaroo(0, 3, 4, 2));
    REQUIRE(!kangaroo(0, 2, 5, 3));
}
