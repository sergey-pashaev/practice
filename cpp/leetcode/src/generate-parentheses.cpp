// generate parentheses

// https://leetcode.com/problems/generate-parentheses/

#include <catch2/catch.hpp>

#include <string>
#include <vector>

using namespace std;

void generate(vector<string>& ret, int n, string s, int o, int c) {
    if (o + c > 2 * n) return;

    if (o == c && o + c == 2 * n) {
        ret.push_back(s);
    }

    if (o < n) {
        // add open
        generate(ret, n, s + '(', o + 1, c);
    }

    if (c < o) {
        // add closed
        generate(ret, n, s + ')', o, c + 1);
    }
}

vector<string> generate_parentheses(int n) {
    vector<string> ret;
    generate(ret, n, string(), 0, 0);
    return ret;
}

TEST_CASE("generate parentheses") {
    REQUIRE(generate_parentheses(3) ==
            vector<string>{"((()))", "(()())", "(())()", "()(())", "()()()"});
}
