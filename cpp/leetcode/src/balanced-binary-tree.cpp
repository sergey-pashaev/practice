// balanced binary tree

// https://leetcode.com/problems/balanced-binary-tree/

#include <catch2/catch.hpp>

using namespace std;

struct node {
    node(int x) : val{x} {}

    int val;
    node* left = nullptr;
    node* right = nullptr;
};

int depth(node* n, int d, bool& balanced) {
    if (!n) return d;

    int l = depth(n->left, d + 1, balanced);
    int r = depth(n->right, d + 1, balanced);
    if (abs(l - r) > 1) balanced = false;
    return max(d, max(l, r));
}

bool is_balanced(node* root) {
    bool balanced = true;
    depth(root, 0, balanced);
    return balanced;
}

TEST_CASE("balanced binary tree") {
    // TODO:
}
