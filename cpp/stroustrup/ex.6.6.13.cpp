#include <cstring>

#include <catch2/catch.hpp>

using namespace std;

const size_t TRAILING_ZERO = 1;

char* cat(const char* s1, const char* s2) {
    char* buf = new char[strlen(s1) + strlen(s2) + TRAILING_ZERO];
    strncpy(buf, s1, strlen(s1));
    strncpy(buf + strlen(s1), s2, strlen(s2));
    buf[strlen(s1) + strlen(s2)] = '\0';
    return buf;
}

TEST_CASE("cat") {
    char* s = nullptr;

    SECTION("empty strings") {
        s = cat("", "");
        REQUIRE(strcmp(s, "") == 0);
    }

    SECTION("one empty string") {
        s = cat("a", "");
        REQUIRE(strcmp(s, "a") == 0);
    }

    SECTION("another empty string") {
        s = cat("", "b");
        REQUIRE(strcmp(s, "b") == 0);
    }

    SECTION("none empty string") {
        s = cat("abc", "def");
        REQUIRE(strcmp(s, "abcdef") == 0);
    }

    delete[] s;
}
