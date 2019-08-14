#include <catch2/catch.hpp>

void Swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void Swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

TEST_CASE("swap by pointers", "[swap]") {
    int a = 1;
    int b = 2;

    REQUIRE(a == 1);
    REQUIRE(b == 2);

    SECTION("normal case") {
        Swap(&a, &b);

        REQUIRE(a == 2);
        REQUIRE(b == 1);
    }

    SECTION("same arguments") {
        Swap(&a, &a);

        // save values as previously
        REQUIRE(a == 1);
        REQUIRE(b == 2);
    }
}

TEST_CASE("swap by reference", "[swap]") {
    int a = 1;
    int b = 2;

    REQUIRE(a == 1);
    REQUIRE(b == 2);

    SECTION("normal case") {
        Swap(a, b);

        REQUIRE(a == 2);
        REQUIRE(b == 1);
    }

    SECTION("same arguments") {
        Swap(a, a);

        // save values as previously
        REQUIRE(a == 1);
        REQUIRE(b == 2);
    }
}
