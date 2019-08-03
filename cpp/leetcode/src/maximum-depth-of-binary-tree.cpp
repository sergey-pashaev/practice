// maximum depth of binary tree

// https://leetcode.com/problems/maximum-depth-of-binary-tree/

#include <catch2/catch.hpp>

#include <algorithm>

using namespace std;

struct node {
    node(int x) : val{x} {}

    int val;
    node* left = nullptr;
    node* right = nullptr;
};

int depth(node* n) {
    if (!n) return 0;
    return max(depth(n->left), depth(n->right)) + 1;
}

int max_depth(node* root) { return depth(root); }

TEST_CASE("maximum depth of binary tree") {
    // TODO:
}
