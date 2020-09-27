#include <catch2/catch.hpp>

#include <memory>

#include "creator.h"

TEST_CASE("OpNewCreator") {
    OpNewCreator<int> creator;
    std::unique_ptr<int> ip(creator.Create());
    REQUIRE(ip);
}

TEST_CASE("MallocCreator") {
    MallocCreator<int> creator;
    std::unique_ptr<int> ip(creator.Create());
    REQUIRE(ip);
}

struct Widget {
    Widget(int v = 42) : value{v} {}
    Widget* Clone() const { return new Widget(value); }

    int value;
};

TEST_CASE("PrototypeCreator") {
    SECTION("empty") {
        PrototypeCreator<Widget> creator;
        REQUIRE(creator.Create() == nullptr);
        REQUIRE(creator.GetPrototype() == nullptr);
    }

    SECTION("valid") {
        Widget prototype{42};
        PrototypeCreator<Widget> creator(&prototype);
        std::unique_ptr<Widget> ip(creator.Create());
        REQUIRE(ip);
        REQUIRE(ip->value == prototype.value);

        creator.SetPrototype(nullptr);
        REQUIRE(creator.Create() == nullptr);
    }
}
