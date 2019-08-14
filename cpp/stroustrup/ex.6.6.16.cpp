#include <cstring>

#include <catch2/catch.hpp>

using namespace std;

int matoi(const char* s) {
    int ret = 0;
    int magnitude = 1;
    for (int i = strlen(s) - 1; i >= 0 && s[i] >= '0' && s[i] <= '9'; --i) {
        ret += (s[i] - '0') * magnitude;
        magnitude *= 10;
    }

    return ret;
}

TEST_CASE("atoi") {
    REQUIRE(matoi("0") == 0);
    REQUIRE(matoi("1") == 1);
    REQUIRE(matoi("12") == 12);
    REQUIRE(matoi("123") == 123);
    REQUIRE(matoi("1234") == 1234);
}
