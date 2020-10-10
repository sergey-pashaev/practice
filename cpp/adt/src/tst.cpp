#include <catch2/catch.hpp>

#include "tst.h"

TEST_CASE("tst") {
    adt::TernarySearchTree tst;
    tst.Insert("hello");
    tst.Insert("hell");
    tst.Insert("jello");
    tst.Insert("hi");
    tst.Insert("hid");

    REQUIRE(tst.Search("hi"));
    REQUIRE(tst.Search("hello"));
    REQUIRE(tst.Search("hell"));
    REQUIRE(tst.Search("hello"));
    REQUIRE(tst.Search("jello"));
    REQUIRE(tst.Search("hid"));

    REQUIRE(!tst.Search("hida"));
    REQUIRE(!tst.Search("h"));
    REQUIRE(!tst.Search("not"));
}
