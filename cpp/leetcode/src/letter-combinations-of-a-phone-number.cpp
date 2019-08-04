// letter combinations of a phone number

// https://leetcode.com/problems/letter-combinations-of-a-phone-number/

#include <catch2/catch.hpp>

#include <map>
#include <string>
#include <vector>

using namespace std;

const map<char, string> m = {
    {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
    {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
};

void comb(vector<string>& ret, string cur, string next) {
    if (next.empty()) {
        ret.push_back(cur);
    } else {
        char d = next[0];
        string letters = m.at(d);
        for (int i = 0; i < letters.size(); ++i) {
            comb(ret, cur + letters[i], next.substr(1));
        }
    }
}

vector<string> letter_combinations(string digits) {
    vector<string> ret;
    if (!digits.empty()) comb(ret, "", digits);
    return ret;
}

TEST_CASE("letter combinations of a phone number") {
    REQUIRE(letter_combinations("23") == vector<string>{"ad", "ae", "af", "bd",
                                                        "be", "bf", "cd", "ce",
                                                        "cf"});
}
