#include <cstring>

#include <catch2/catch.hpp>

using namespace std;

const int TRAILING_ZERO = 1;

void rev(char* s) {
    size_t sz = strlen(s);
    for (size_t i = 0; sz > 1 && i < sz / 2; ++i) {
        char tmp = s[i];
        s[i] = s[sz - i - TRAILING_ZERO];
        s[sz - i - TRAILING_ZERO] = tmp;
    }
}

TEST_CASE("rev") {
    SECTION("empty string") {
        char s[] = "";
        rev(s);
        REQUIRE(strcmp(s, "") == 0);
    }

    SECTION("1 char") {
        char s[] = "a";
        rev(s);
        REQUIRE(strcmp(s, "a") == 0);
    }

    SECTION("2 char") {
        char s[] = "ab";
        rev(s);
        REQUIRE(strcmp(s, "ba") == 0);
    }

    SECTION("3 char") {
        char s[] = "abc";
        rev(s);
        REQUIRE(strcmp(s, "cba") == 0);
    }

    SECTION("4 char") {
        char s[] = "abcd";
        rev(s);
        REQUIRE(strcmp(s, "dcba") == 0);
    }
}
