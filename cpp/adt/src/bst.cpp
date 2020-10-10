#include <catch2/catch.hpp>

#include <iostream>

#include "bst.h"

TEST_CASE("tst") {
    adt::BinarySearchTree bst;
    bst.Insert(2);
    bst.Insert(1);
    bst.Insert(3);
    bst.Insert(4);
    bst.Insert(2);

    bst.Traverse([](int lvl, int v) {
        while (lvl--) std::cout << ' ';
        std::cout << v << '\n';
    });
}
