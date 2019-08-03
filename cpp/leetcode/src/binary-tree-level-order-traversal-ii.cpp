// binary tree level order traversal II

// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

struct node {
    node(int x) : val{x} {}

    int val;
    node* left = nullptr;
    node* right = nullptr;
};

void traverse(vector<vector<int>>& v, node* root, int lvl) {
    if (!root) return;

    // create vector for new level if needed
    if (lvl + 1 > v.size()) v.emplace_back();

    traverse(v, root->left, lvl + 1);
    traverse(v, root->right, lvl + 1);

    // put node in appropriate vector
    v[lvl].push_back(root->val);
}

vector<vector<int>> levelOrderBottom(node* root) {
    vector<vector<int>> ret;
    traverse(ret, root, 0);
    reverse(begin(ret), end(ret));
    return ret;
}

TEST_CASE(" binary tree level order traversal IIb") {
    // TODO:
}
