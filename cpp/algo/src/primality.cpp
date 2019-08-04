// primality

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

bool primality(int n) {
    vector<int> prime(n + 1, 1);
    prime[0] = 0;
    prime[1] = 0;
    for (int i = 2; i * i <= n; ++i) {
        if ((i % 2 != 0 && prime[i]) || i == 2) {
            // stroke out all up to i*i
            for (int j = i * i; j <= n; j += i) prime[j] = false;
        }
    }
    return prime[n];
}

TEST_CASE("primality") {
    REQUIRE(!primality(1));
    REQUIRE(primality(2));
    REQUIRE(primality(3));
    REQUIRE(!primality(4));
    REQUIRE(primality(5));
    REQUIRE(!primality(6));
    REQUIRE(primality(7));
    REQUIRE(!primality(14582734));
}
