// ctci fibonacci numbers

// https://www.hackerrank.com/challenges/ctci-fibonacci-numbers/problem

#include <catch2/catch.hpp>

using namespace std;

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int pp = 0;
    int p = 1;
    int f = 0;
    for (int i = 2; i <= n; ++i) {
        f = pp + p;
        pp = p;
        p = f;
    }
    return f;
}

TEST_CASE("ctci fibonacci numbers") {
    REQUIRE(fibonacci(0) == 0);
    REQUIRE(fibonacci(1) == 1);
    REQUIRE(fibonacci(2) == 1);
    REQUIRE(fibonacci(3) == 2);
    REQUIRE(fibonacci(4) == 3);
    REQUIRE(fibonacci(5) == 5);
    REQUIRE(fibonacci(6) == 8);
}
