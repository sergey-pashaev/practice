#include <iostream>
#include <string>

#include <catch2/catch.hpp>

using namespace std;

size_t CountCharPair(const string& str, const char chars[2]) {
    size_t count = 0;
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (*it == chars[0] && (it + 1) != str.end() && *(it + 1) == chars[1]) {
            ++count;
        }
    }

    return count;
}

size_t CountCharPair(const char* str, const char chars[2]) {
    size_t count = 0;
    while (*str) {
        if (*str == chars[0] && *(str + 1) && *(str + 1) == chars[1]) {
            ++count;
        }

        ++str;
    }

    return count;
}

TEST_CASE("count char pairs", "[char pair]") {
    const string str{"xabaacbaxabb"};
    const char chars[] = {'a', 'b'};

    REQUIRE(CountCharPair(str, chars) == 2);
    REQUIRE(CountCharPair(str.c_str(), chars) == 2);
}
