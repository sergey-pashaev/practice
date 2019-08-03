// same tree

// https://leetcode.com/problems/same-tree/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

struct node {
    node(int x) : val{x} {}

    int val;
    node* left = nullptr;
    node* right = nullptr;
};

bool is_same_tree(node* p, node* q) {
    if (p && q) {
        if (p->val != q->val) return false;
        return is_same_tree(p->left, q->left) &&
               is_same_tree(p->right, q->right);
    } else {
        return !p && !q;
    }
}

TEST_CASE("same tree") {
    // TODO:
}
