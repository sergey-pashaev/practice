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
