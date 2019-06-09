#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch.hpp>

using namespace std;

struct Widget {
    int id;
    string name;
};

bool operator<(const Widget& lhs, const Widget& rhs) { return lhs.id < rhs.id; }

struct WidgetStringComparator {
    bool operator()(const Widget& lhs, const Widget& rhs) {
        return lhs.name < rhs.name;
    }
};

TEST_CASE("sorting") {
    vector<Widget> v = {{0, "zero"}, {1, "first"}, {2, "second"}};

    SECTION("sort using default operator<") {
        sort(begin(v), end(v));
        REQUIRE(is_sorted(begin(v), end(v)));
    }

    SECTION("sort using functional object comparator") {
        sort(begin(v), end(v), WidgetStringComparator());
        REQUIRE(is_sorted(begin(v), end(v), WidgetStringComparator()));
    }

    SECTION("sort using lambda as comparator") {
        auto cmp = [](const Widget& lhs, const Widget& rhs) -> bool {
            return lhs.id < rhs.id;
        };

        sort(begin(v), end(v), cmp);
        REQUIRE(is_sorted(begin(v), end(v), cmp));
    }
}

template <typename Fwd>
bool is_unique(Fwd first, Fwd last) {
    // Search range [first, last) for two consecutive identical
    // elements and make sure no such elements found.
    return adjacent_find(first, last) == last;
}

TEST_CASE("remove duplicates") {
    vector<int> v = {0, 1, 1, 2, 3, 2, 2};

    // sort first since unique removes only consecutive duplicates
    sort(begin(v), end(v));

    auto new_end = unique(begin(v), end(v));
    v.erase(new_end, end(v));

    REQUIRE(v.size() == 4);
    REQUIRE(is_unique(begin(v), end(v)));
}

vector<size_t> find_all_pos(const string& str, const string& pattern) {
    vector<size_t> ret;
    for (auto pos = str.find(pattern, 0); pos != string::npos;
         pos = str.find(pattern, pos + pattern.size())) {
        ret.push_back(pos);
    }

    return ret;
}

TEST_CASE("find all positions of string") {
    string s = "abc def ghf abc def";

    SECTION("0 matches") {
        auto matches = find_all_pos(s, "xyz");
        REQUIRE(matches.empty());
    }

    SECTION("1 match") {
        auto matches = find_all_pos(s, "ghf");
        REQUIRE(matches.size() == 1);
        REQUIRE(matches[0] == 8);
    }

    SECTION("2 matches") {
        auto matches = find_all_pos(s, "abc");
        REQUIRE(matches.size() == 2);
        REQUIRE(matches[0] == 0);
        REQUIRE(matches[1] == 12);
    }
}

vector<string_view> find_all_view(const string& str, string_view pattern) {
    vector<string_view> ret;
    const char* data = str.data();
    const size_t pattern_sz = pattern.size();
    for (auto pos = str.find(pattern, 0); pos != string::npos;
         pos = str.find(pattern, pos + pattern_sz)) {
        ret.emplace_back(data + pos, pattern_sz);
    }

    return ret;
}

TEST_CASE("find all views of string") {
    string s = "abc def ghf abc def";

    SECTION("0 matches") {
        auto matches = find_all_view(s, "xyz");
        REQUIRE(matches.empty());
    }

    SECTION("1 match") {
        const char* pattern = "ghf";
        auto matches = find_all_view(s, pattern);
        REQUIRE(matches.size() == 1);
        REQUIRE(matches[0] == pattern);
    }
}

void to_lower(string& s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void to_upper(string& s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

TEST_CASE("cases") {
    string s = "Hello Darkness my old friend.";

    SECTION("to lower case") {
        to_lower(s);
        REQUIRE(s == "hello darkness my old friend.");
    }

    SECTION("to upper case") {
        to_upper(s);
        REQUIRE(s == "HELLO DARKNESS MY OLD FRIEND.");
    }
}
