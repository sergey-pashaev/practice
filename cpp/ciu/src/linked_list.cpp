#include <catch.hpp>

#include <psv/linked_list.h>

using psv::LinkedList;

TEST_CASE("list construction", "[linked_list][template]") {
    typedef int T;

    LinkedList<T> l;

    REQUIRE(l.IsEmpty());
    REQUIRE(l.Size() == 0);
    REQUIRE_THROWS_AS(l.At(0), std::out_of_range);

    SECTION("push front at empty") {
        LinkedList<T> l;
        l.PushFront(0);
        REQUIRE(l.Size() == 1);
        REQUIRE(l.At(0) == 0);
    }

    SECTION("push back at empty") {
        LinkedList<T> l;
        l.PushBack(0);
        REQUIRE(l.Size() == 1);
        REQUIRE(l.At(0) == 0);
    }

    SECTION("pop back empty list") {
        LinkedList<T> l;
        REQUIRE_THROWS_AS(l.Back(), std::out_of_range);
        REQUIRE_THROWS_AS(l.PopBack(), std::out_of_range);
    }

    SECTION("pop front empty list") {
        LinkedList<T> l;
        REQUIRE_THROWS_AS(l.Front(), std::out_of_range);
        REQUIRE_THROWS_AS(l.PopFront(), std::out_of_range);
    }

    l.PushBack(1);
    REQUIRE(!l.IsEmpty());
    REQUIRE(l.Size() == 1);
    REQUIRE(l.At(0) == 1);

    l.PushBack(2);
    REQUIRE(l.Size() == 2);
    REQUIRE(l.At(1) == 2);

    l.PushBack(3);
    REQUIRE(l.Size() == 3);
    REQUIRE(l.At(2) == 3);

    l.PushFront(0);
    REQUIRE(l.Size() == 4);
    REQUIRE(l.At(0) == 0);
    REQUIRE(l.At(1) == 1);
    REQUIRE(l.At(2) == 2);
    REQUIRE(l.At(3) == 3);

    REQUIRE(l.PopBack() == 3);
    REQUIRE(l.Size() == 3);
    REQUIRE(l.At(0) == 0);
    REQUIRE(l.At(1) == 1);
    REQUIRE(l.At(2) == 2);

    REQUIRE(l.PopFront() == 0);
    REQUIRE(l.Size() == 2);
    REQUIRE(l.At(0) == 1);
    REQUIRE(l.At(1) == 2);

    REQUIRE(l.Front() == 1);
    REQUIRE(l.Back() == 2);
}

TEST_CASE("list copy ctor", "[linked_list][template]") {
    typedef int T;

    LinkedList<T> l1;
    l1.PushBack(1);
    l1.PushBack(2);
    l1.PushBack(3);

    LinkedList<T> l2(l1);
    REQUIRE(l2.At(0) == 1);
    REQUIRE(l2.At(1) == 2);
    REQUIRE(l2.At(2) == 3);
}
