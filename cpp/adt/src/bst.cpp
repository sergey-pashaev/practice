#include <catch2/catch.hpp>

#include <iostream>

#include "bst.h"

using namespace std;

TEST_CASE("tst") {
    psv::BinarySearchTree bst;
    bst.Insert(2);
    bst.Insert(1);
    bst.Insert(3);
    bst.Insert(4);
    bst.Insert(2);

    bst.Traverse([](int lvl, int v) {
        while (lvl--) cout << ' ';
        cout << v << '\n';
    });
}
