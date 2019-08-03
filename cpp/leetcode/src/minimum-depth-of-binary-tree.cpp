// minimum depth of binary tree

// https://leetcode.com/problems/minimum-depth-of-binary-tree/

#include <catch2/catch.hpp>

#include <queue>

using namespace std;

struct node {
    node(int x) : val{x} {}

    int val;
    node* left = nullptr;
    node* right = nullptr;
};

int min_depth(node* root) {
    queue<node*> q;
    if (root) q.push(root);
    int lvl = 0;
    while (!q.empty()) {
        ++lvl;
        int k = q.size();

        // process all nodes added on previous iteration
        for (int i = 0; i < k; ++i) {
            node* n = q.front();
            q.pop();

            bool leaf = !n->left && !n->right;
            if (leaf) return lvl;

            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }

    return lvl;
}

TEST_CASE("minimum depth of binary tree") {
    // TODO:
}
