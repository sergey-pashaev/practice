#include <catch2/catch.hpp>

size_t strlen(const char* p) {
    size_t len = 0;
    while (*p++) ++len;
    return len;
}

size_t strcpy(const char* from, char* to) {
    size_t written = 0;
    while ((*to++ = *from++)) ++written;
    *to = '\0';
    return written;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 == *s2) {
        if (*s1 == '\0') return 0;

        ++s1;
        ++s2;
    }

    return *s1 - *s2;
}

TEST_CASE("strlen") {
    REQUIRE(strlen("") == 0);
    REQUIRE(strlen("a") == 1);
    REQUIRE(strlen("ab") == 2);
    REQUIRE(strlen("abc") == 3);
    REQUIRE(strlen("abc\0de") == 3);
    REQUIRE(strlen("\0abcde") == 0);
}

TEST_CASE("strcmp") {
    REQUIRE(strcmp("", "") == 0);
    REQUIRE(strcmp("ab", "ab") == 0);
    REQUIRE(strcmp("aa", "bb") == -1);
    REQUIRE(strcmp("ba", "aa") == 1);
    REQUIRE(strcmp("aa", "ab") == -1);
    REQUIRE(strcmp("aaa", "bb") == -1);
    REQUIRE(strcmp("baa", "aa") == 1);
    REQUIRE(strcmp("aaa", "ab") == -1);
}

TEST_CASE("strcpy") {
    char buf[64];
    REQUIRE(strcpy("abc", buf) == 3);
    REQUIRE(strcmp("abc", buf) == 0);

    REQUIRE(strcpy("", buf) == 0);
    REQUIRE(strcmp("", buf) == 0);
}
