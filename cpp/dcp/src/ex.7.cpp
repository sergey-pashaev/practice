// ex.7

// Given the mapping a = 1, b = 2, ... z = 26, and an encoded message,
// count the number of ways it can be decoded.

// For example, the message '111' would give 3, since it could be
// decoded as 'aaa', 'ka', and 'ak'.

// You can assume that the messages are decodable. For example, '001'
// is not allowed.

#include <catch2/catch.hpp>

using namespace std;

int ways_to_decode(const char* s, int size, vector<int>& memo) {
    // base cases
    if (size < 1) return 1;
    if (!s) return 1;

    // zero char
    int n1 = s[0] - '0';
    if (n1 == 0) return 0;

    if (memo[size] != -1) return memo[size];

    int w = ways_to_decode(s + 1, size - 1, memo);
    if (size > 1) {
        int n2 = s[1] - '0';
        if ((n1 == 1 && n2 <= 9) || (n2 == 2 && n2 <= 6)) {
            w += ways_to_decode(s + 2, size - 2, memo);
        }
    }

    memo[size] = w;

    return w;
}

int ways_to_decode(const char* s, int size) {
    vector<int> memo(size + 1, -1);
    memo[0] = 1;
    return ways_to_decode(s, size, memo);
}

TEST_CASE("ex.7") {
    REQUIRE(ways_to_decode("111", 3) == 3);
    REQUIRE(ways_to_decode("011", 3) == 0);
}
