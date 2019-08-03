// path sum

// https://leetcode.com/problems/path-sum/

#include <catch2/catch.hpp>

using namespace std;

struct TreeNode {
    TreeNode(int x) : val{x} {}

    int val;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
};

bool has_path_sum(TreeNode *root, int sum) {
    if (!root) return false;
    bool leaf = !root->left && !root->right;
    if (leaf && root->val == sum) return true;
    bool l = has_path_sum(root->left, sum - root->val);
    bool r = has_path_sum(root->right, sum - root->val);
    return l || r;
}

TEST_CASE("path sum") {
    // TODO:
}
