// ex.5

// cons(a, b) constructs a pair, and car(pair) and cdr(pair) returns
// the first and last element of that pair. For example, car(cons(3,
// 4)) returns 3, and cdr(cons(3, 4)) returns 4.

// Given this implementation of cons:

// def cons(a, b):
//     def pair(f):
//         return f(a, b)
//     return pair
// Implement car and cdr.

#include <catch2/catch.hpp>

#include <functional>

using namespace std;

using func = function<int(int, int)>;

using callable_pair = function<int(func)>;

// returns function, which takes function as argument to call it with
// a and b
callable_pair cons(int a, int b) {
    return [a, b](func c) { return c(a, b); };
}

// takes callable pair and calls it w/ lambda which returns first
// argument
int car(callable_pair cpair) {
    return cpair([](int a, int) { return a; });
}

// takes callable pair and calls it / lambda whick return second
// argument
int cdr(callable_pair cpair) {
    return cpair([](int, int b) { return b; });
}

TEST_CASE("ex.5") {
    REQUIRE(car(cons(3, 4)) == 3);
    REQUIRE(cdr(cons(3, 4)) == 4);
    // TODO: REQUIRE(cdr(car(cons(cons(1, 2), 4))) == 2);
}
