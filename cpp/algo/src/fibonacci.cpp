#include <catch2/catch.hpp>

#include <iostream>

int fibonacci(int n) {
    if (n == 0) return 0;

    int prev = 0;
    int curr = 1;
    int next = 0;

    for (int i = 1; i < n; ++i) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}

TEST_CASE("fibonacci") {
    REQUIRE(fibonacci(0) == 0);
    REQUIRE(fibonacci(1) == 1);
    REQUIRE(fibonacci(2) == 1);
    REQUIRE(fibonacci(3) == 2);
    REQUIRE(fibonacci(4) == 3);
    REQUIRE(fibonacci(5) == 5);
}
