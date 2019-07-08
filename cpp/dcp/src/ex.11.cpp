// ex.11

// Implement an autocomplete system. That is, given a query string s
// and a set of all possible query strings, return all strings in the
// set that have s as a prefix.

// For example, given the query string de and the set of strings [dog,
// deer, deal], return [deer, deal].

// Hint: Try preprocessing the dictionary into a more efficient data
// structure to speed up queries.

#include <catch2/catch.hpp>

#include <set>

using namespace std;

// naive version
set<string> complete(const string& input, const set<string>& completions) {
    set<string> ret;

    for (const string& s : completions) {
        if (s.find(input) == 0) {
            ret.insert(s);
        }
    }

    return ret;
}

// TODO: more efficient data structure

TEST_CASE("ex.11") {
    set<string> completions = {"dog", "deer", "deal"};

    REQUIRE(complete("de", completions) == set<string>({"deer", "deal"}));
}
