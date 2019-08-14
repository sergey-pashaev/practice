#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>

#include <catch2/catch.hpp>

using namespace std;

void ReadSortedWords(istringstream& in, ostringstream& out) {
    set<string> words;
    string word;

    while (in >> word && word != "quit") {
        words.insert(word);
    }

    for (const auto& word : words) {
        out << word << " ";
    }
}

void ReadWords(istringstream& in, ostringstream& out) {
    unordered_set<string> unique_words;
    list<string> words;
    string word;

    while (in >> word && word != "quit") {
        if (unique_words.insert(word).second) {
            words.push_back(word);
        }
    }

    for (const auto& word : words) {
        out << word << " ";
    }
}

TEST_CASE("unique words") {
    istringstream in{"cd ab ef ab ef gh gh jk"};

    ostringstream out{"cd ab ef gh jk "};
    ostringstream sorted_out{"ab cd ef gh jk "};

    SECTION("non sorted") {
        ostringstream tmp;
        ReadWords(in, tmp);

        REQUIRE(tmp.str() == out.str());
    }

    SECTION("sorted") {
        ostringstream tmp;
        ReadSortedWords(in, tmp);

        REQUIRE(tmp.str() == sorted_out.str());
    }
}
