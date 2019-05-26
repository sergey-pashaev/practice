#include <catch.hpp>

#include "circular_buffer.h"

TEST_CASE("circular buffer") {
    psv::CircularBuffer<int> b(3);

    REQUIRE(b.Empty());
    REQUIRE(b.Size() == 0);
    REQUIRE(!b.Full());
    REQUIRE_THROWS_AS(b.Read(), std::length_error);
    REQUIRE_THROWS_AS(b.Front(), std::length_error);
    REQUIRE_THROWS_AS(b.Back(), std::length_error);

    b.Write(1);

    REQUIRE(!b.Empty());
    REQUIRE(!b.Full());
    REQUIRE(b.Size() == 1);
    REQUIRE(b.Front() == 1);
    REQUIRE(b.Back() == 1);

    b.Write(2);

    REQUIRE(!b.Empty());
    REQUIRE(!b.Full());
    REQUIRE(b.Size() == 2);
    REQUIRE(b.Front() == 1);
    REQUIRE(b.Back() == 2);

    b.Write(3);

    REQUIRE(!b.Empty());
    REQUIRE(b.Full());
    REQUIRE(b.Size() == 3);
    REQUIRE(b.Front() == 1);
    REQUIRE(b.Back() == 3);

    b.Write(4);

    REQUIRE(!b.Empty());
    REQUIRE(b.Full());
    REQUIRE(b.Size() == 3);
    REQUIRE(b.Front() == 2);
    REQUIRE(b.Back() == 4);

    REQUIRE(b.Read() == 2);

    REQUIRE(!b.Empty());
    REQUIRE(!b.Full());
    REQUIRE(b.Size() == 2);
    REQUIRE(b.Front() == 3);
    REQUIRE(b.Back() == 4);

    REQUIRE(b.Read() == 3);

    REQUIRE(!b.Empty());
    REQUIRE(!b.Full());
    REQUIRE(b.Size() == 1);
    REQUIRE(b.Front() == 4);
    REQUIRE(b.Back() == 4);

    REQUIRE(b.Read() == 4);

    REQUIRE(b.Empty());
    REQUIRE(!b.Full());
    REQUIRE(b.Size() == 0);
}
