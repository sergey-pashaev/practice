// balanced brackets

// https://www.hackerrank.com/challenges/balanced-brackets/problem

#include <catch2/catch.hpp>

#include <stack>
#include <string>

using namespace std;

// Complete the isBalanced function below.
bool is_balanced(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            if ((c == ')' && top == '(') || (c == ']' && top == '[') ||
                (c == '}' && top == '{')) {
                st.pop();
            } else {
                return false;
            }
        }
    }

    return st.empty();
}

TEST_CASE("balanced brackets") {
    REQUIRE(is_balanced("{[()]}"));
    REQUIRE(!is_balanced("{[(])}"));
    REQUIRE(is_balanced("{{[[(())]]}}"));
}
