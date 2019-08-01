// grading

// https://www.hackerrank.com/challenges/grading/problem

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

int grade(int g) {
    int next = ((g / 5) + 1) * 5;
    if (g >= 38 && next - g < 3) return next;
    return g;
}

vector<int> grading(const vector<int>& grades) {
    vector<int> ret(grades);
    for (int& g : ret) {
        g = grade(g);
    }
    return ret;
}

TEST_CASE("grading") {
    REQUIRE(grading({73, 67, 38, 33}) == vector<int>{75, 67, 40, 33});
}
