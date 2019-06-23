// ex.1.3

// Строки, нечувствительные к регистру. Часть 2

#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

#include <catch2/catch.hpp>

int memicmp(const char* s1, const char* s2, std::size_t n) {
    const unsigned char* p1 = reinterpret_cast<const unsigned char*>(s1);
    const unsigned char* p2 = reinterpret_cast<const unsigned char*>(s2);
    while (n--)
        if (std::toupper(*p1) != std::toupper(*p2))
            return *p1 - *p2;
        else
            p1++, p2++;
    return 0;
}

/// case insensetive char trait
struct ci_char_traits : public std::char_traits<char> {
    static bool eq(char c1, char c2) {
        return std::toupper(c1) == std::toupper(c2);
    };

    static bool lt(char c1, char c2) {
        return std::toupper(c1) < std::toupper(c2);
    }

    static int compare(const char* s1, const char* s2, std::size_t n) {
        return memicmp(s1, s2, n);
    }

    static const char* find(const char* s, int n, char a) {
        while (n-- > 0 && std::toupper(*s) != std::toupper(a)) {
            ++s;
        }
        return n >= 0 ? s : 0;
    }
};

using ci_string = std::basic_string<char, ci_char_traits>;

TEST_CASE("main") {
    ci_string s("AbCdE");
    REQUIRE(s == "abcde");
    REQUIRE(s == "ABCDE");

    REQUIRE(std::strcmp(s.c_str(), "AbCdE") == 0);
    REQUIRE(std::strcmp(s.c_str(), "abcde") != 0);

    // it is not good approach to design such functionality, for example:
    using yz_string = std::string;  // this is string w/ another char traits
    ci_string ci("aAa");
    yz_string yz("AAa");

    // which char trait should be used here?
    // REQUIRE(ci == yz);
}

// Q: Is it save to derive ci_char_traits from std::char_traits<char> like we
// done? A: Yes. It violates LSP but conforms to GLSP.

// Q: Why this code doesn't compile?
// ci_string s = "aBc";
// std::cout << s << '\n';
// A: cout == basic_ostream(char, traits), ci_string has different
// type of traits. So we will provide appropriate overload.

std::ostream& operator<<(std::ostream& os, const ci_string& str) {
    os << str.c_str();
    return os;
}

TEST_CASE("ostream") {
    ci_string s = "aBc";
    std::cout << s << '\n';
}

// Q: How ci_string would work with +, +=, = operators and std::string ?
// A: Add operator+() overload for ci_string or use .c_str() function.

std::string operator+(const std::string& s1, const ci_string& s2) {
    return s1 + s2.c_str();
}

std::string operator+(const ci_string& s1, const std::string& s2) {
    return s1.c_str() + s2;
}

TEST_CASE("concat") {
    std::string a = "aaa";
    ci_string b = "bbb";

    std::cout << a + b << '\n';
    std::cout << b + a << '\n';
}
