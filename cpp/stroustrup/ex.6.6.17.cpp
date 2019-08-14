#include <cstring>

#include <catch2/catch.hpp>

using namespace std;

int itoa(int n, char* s) {
    bool minus = false;
    if (n < 0) {
        *s++ = '-';
        n = -n;
    }

    // count number of digits
    size_t char_num = 1;  // at least one
    int t = n;
    while (t /= 10) {
        ++char_num;
    }

    *(s + char_num) = '\0';
    while (char_num) {
        *(s + char_num-- - 1) = '0' + n % 10;
        n /= 10;
    }

    return 0;
}

TEST_CASE("itoa") {
    char buf[64] = "";

    itoa(-1, buf);
    REQUIRE(strcmp(buf, "-1") == 0);

    itoa(0, buf);
    REQUIRE(strcmp(buf, "0") == 0);

    itoa(1, buf);
    REQUIRE(strcmp(buf, "1") == 0);

    itoa(12, buf);
    REQUIRE(strcmp(buf, "12") == 0);

    itoa(123, buf);
    REQUIRE(strcmp(buf, "123") == 0);

    itoa(1234, buf);
    REQUIRE(strcmp(buf, "1234") == 0);
}
