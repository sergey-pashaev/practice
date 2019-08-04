// stones and jewelry

// Даны две строки строчных латинских символов: строка J и строка
// S. Символы, входящие в строку J, — «драгоценности», входящие в
// строку S — «камни». Нужно определить, какое количество символов из
// S одновременно являются «драгоценностями». Проще говоря, нужно
// проверить, какое количество символов из S входит в J.

#include <catch2/catch.hpp>

#include <string>
#include <unordered_set>

using namespace std;

int f(const string& j, const string& s) {
    unordered_set<char> jset(j.begin(), j.end());
    int ret = 0;
    for (char c : s) {
        ret += jset.count(c);
    }
    return ret;
}

TEST_CASE("stones and jewelry") {
    // jewelry, stones
    REQUIRE(f("jewelry", "stones") == 1);
    REQUIRE(f("abcd", "aacc") == 4);
    REQUIRE(f("abc", "d") == 0);
}
