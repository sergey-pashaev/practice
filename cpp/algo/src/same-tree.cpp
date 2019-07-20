// same tree

#include <catch2/catch.hpp>

using namespace std;

struct Node {
    explicit Node(int v) : v{v}, l{nullptr}, r{nullptr} {}

    int v;
    Node* l;
    Node* r;
};

void clean(Node* root) {
    if (!root) return;

    if (root->l) {
        clean(root->l);
        delete root->l;
        root->l = nullptr;
    }

    if (root->r) {
        clean(root->r);
        delete root->r;
        root->r = nullptr;
    }

    root = nullptr;
}

bool same_tree(Node* root1, Node* root2) {
    if (!root1 && !root2) return true;
    if (!root1 || !root2) return false;
    return root1->v == root2->v && same_tree(root1->l, root2->l) &&
           same_tree(root1->r, root2->r);
}

TEST_CASE("same tree") {
    REQUIRE(same_tree(nullptr, nullptr));

    Node* t1 = new Node(1);
    t1->l = new Node(2);
    t1->r = new Node(3);
    t1->r->r = new Node(4);

    REQUIRE(!same_tree(t1, nullptr));

    Node* t2 = new Node(1);
    t2->l = new Node(2);
    t2->r = new Node(3);
    t2->r->r = new Node(4);

    REQUIRE(same_tree(t1, t2));

    Node* t3 = new Node(1);
    t3->l = new Node(2);
    t3->r = new Node(3);

    REQUIRE(!same_tree(t1, t3));

    clean(t1);
    delete t1;
    clean(t2);
    delete t2;
    clean(t3);
    delete t3;
}
