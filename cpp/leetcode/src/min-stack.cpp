// min stack

// https://leetcode.com/problems/min-stack/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

class MinStack {
   public:
    void push(int x) {
        int min = numeric_limits<int>::max();
        if (m_.size()) min = m_.back();
        if (x < min) min = x;
        l_.push_back(x);
        m_.push_back(min);
    }

    void pop() {
        l_.pop_back();
        m_.pop_back();
    }

    int top() { return l_.back(); }

    int get_min() { return m_.back(); }

   private:
    vector<int> l_;
    vector<int> m_;
};

TEST_CASE("min stack") {
    MinStack ms;

    ms.push(-2);
    ms.push(0);
    ms.push(-3);
    REQUIRE(ms.get_min() == -3);
    ms.pop();
    REQUIRE(ms.top() == 0);
    ms.pop();
    REQUIRE(ms.get_min() == -2);
}
