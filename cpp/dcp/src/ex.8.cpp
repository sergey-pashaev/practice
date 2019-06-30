// ex.8

// A unival tree (which stands for "universal value") is a tree where
// all nodes under it have the same value.

// Given the root to a binary tree, count the number of unival
// subtrees.

// For example, the following tree has 5 unival subtrees:

//   0
//  / \
// 1   0
//    / \
//   1   0
//  / \
// 1   1

#include <catch2/catch.hpp>

using namespace std;

struct Node {
    Node(int v, Node* l = nullptr, Node* r = nullptr) : v{v}, l{l}, r{r} {}

    int v = 0;
    Node* l = nullptr;
    Node* r = nullptr;

    static void clean(Node* root) {
        if (root->l) {
            clean(root->l);
            root->l = nullptr;
        }
        if (root->l) {
            clean(root->l);
            root->l = nullptr;
        }

        delete root;
    }
};

void f(Node* node, Node* parent, int& acc) {
    if (node->l) ++acc;
    if (node->r) ++acc;

    if (parent && node->v != parent->v && acc > 0) {
        --acc;
    }

    if (node->l) {
        f(node->l, node, acc);
    }

    if (node->r) {
        f(node->r, node, acc);
    }
}

int f(Node* root) {
    if (!root) return 0;
    int acc = 1;
    f(root, nullptr, acc);
    return acc;
}

TEST_CASE("ex.8") {
    SECTION("task example") {
        //   0
        //  / \
        // 1   0
        //    / \
        //   1   0
        //  / \
        // 1   1

        Node* root = new Node(
            0, new Node(1),
            new Node(0, new Node(1, new Node(1), new Node(1)), new Node(0)));

        REQUIRE(f(root) == 5);

        Node::clean(root);
    }

    SECTION("empty tree") {
        Node* root = nullptr;
        REQUIRE(f(root) == 0);
    }

    SECTION("single node") {
        Node* root = new Node(1);
        REQUIRE(f(root) == 1);
        Node::clean(root);
    }

    SECTION("two same nodes") {
        Node* root = new Node(1, new Node(1));
        REQUIRE(f(root) == 2);
        Node::clean(root);
    }

    SECTION("two different nodes") {
        Node* root = new Node(1, new Node(0));
        REQUIRE(f(root) == 1);
        Node::clean(root);
    }

    SECTION("3 nodes") {
        //   0
        //  / \
        // 1   0
        Node* root = new Node(0, new Node(1), new Node(0));
        REQUIRE(f(root) == 2);
        Node::clean(root);
    }

    SECTION("0 1 0 1") {
        // 0 - 1 - 0 - 1
        Node* root = new Node(0, new Node(1, new Node(0, new Node(1))));
        REQUIRE(f(root) == 1);
        Node::clean(root);
    }
}
