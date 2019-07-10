#include <catch2/catch.hpp>

#include "trie.h"

TEST_CASE("trie") {
    psv::TrieRWays<26> t;

    t.Insert("some");
    t.Insert("words");
    t.Insert("stored");
    t.Insert("in");
    t.Insert("this");
    t.Insert("tree");

    REQUIRE(t.Lookup("some"));
    REQUIRE(t.Lookup("words"));
    REQUIRE(t.Lookup("stored"));
    REQUIRE(t.Lookup("in"));
    REQUIRE(t.Lookup("this"));
    REQUIRE(t.Lookup("tree"));

    REQUIRE(!t.Lookup("but"));
    REQUIRE(!t.Lookup("not"));
    REQUIRE(!t.Lookup("zis"));
    REQUIRE(!t.Lookup("ones"));
}
