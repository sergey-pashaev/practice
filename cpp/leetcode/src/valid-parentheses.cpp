// valid parentheses

// https://leetcode.com/problems/valid-parentheses/

// Given a string containing just the characters '(', ')', '{', '}',
// '[' and ']', determine if the input string is valid.

// An input string is valid if:

// Open brackets must be closed by the same type of brackets.
// Open brackets must be closed in the correct order.
// Note that an empty string is also considered valid.

// Example 1:
// Input: "()"
// Output: true

// Example 2:
// Input: "()[]{}"
// Output: true

// Example 3:
// Input: "(]"
// Output: false

// Example 4:
// Input: "([)]"
// Output: false

// Example 5:
// Input: "{[]}"
// Output: true

#include <catch2/catch.hpp>

#include <stack>
#include <string>

using namespace std;

char pairc(char c) {
    switch (c) {
        case '(':
            return ')';
        case ')':
            return '(';
        case '[':
            return ']';
        case ']':
            return '[';
        case '{':
            return '}';
        case '}':
            return '{';
    }

    return 0;
}

bool is_valid(const std::string& s) {
    stack<char> stack;

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stack.empty()) return false;
            if (stack.top() != pairc(c)) return false;
            stack.pop();
        }
    }

    return stack.empty();
}

TEST_CASE("valid parentheses") {
    REQUIRE(is_valid("()"));
    REQUIRE(is_valid("()[]{}"));
    REQUIRE(is_valid("()[]{}"));
    REQUIRE(!is_valid("(]"));
    REQUIRE(!is_valid("([)]"));
    REQUIRE(is_valid("{[]}"));
    REQUIRE(!is_valid("([)"));
}
