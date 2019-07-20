// fizzbuzz

#include <catch2/catch.hpp>

#include <iostream>

using namespace std;

void fizzbuzz(int n) {
    for (int i = 1; i <= n; ++i) {
        bool fizz = i % 3 == 0;
        bool buzz = i % 5 == 0;
        if (fizz && buzz) {
            cout << i << " fizzbuzz\n";
        } else if (fizz) {
            cout << i << " fizz\n";
        } else if (buzz) {
            cout << i << " buzz\n";
        } else {
            cout << i << '\n';
        }
    }
}

TEST_CASE("fizzbuzz") { fizzbuzz(20); }
