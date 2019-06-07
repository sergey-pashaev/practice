#include <algorithm>
#include <string>
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
