// tree height of a binary tree

// The height of a binary tree is the number of edges between the
// tree's root and its furthest leaf. For example, the following
// binary tree is of height 2:

//      4
//    /   \
//   2     6
//  / \   / \
// 1   3 5   7

// Function Description

// Complete the getHeight or height function in the editor. It must return the
// height of a binary tree as an integer.

// getHeight or height has the following parameter(s):

// root: a reference to the root of a binary tree.
// Note -The Height of binary tree with single node is taken as zero.

#include <catch2/catch.hpp>

#include <algorithm>

using namespace std;

class Node {
   public:
    int data;
    Node* left;
    Node* right;
    Node(int d) {
        data = d;
        left = NULL;
        right = NULL;
    }
};

class BinaryTree {
   public:
    Node* insert(Node* root, int data) {
        if (root == NULL) {
            return new Node(data);
        } else {
            Node* cur;
            if (data <= root->data) {
                cur = insert(root->left, data);
                root->left = cur;
            } else {
                cur = insert(root->right, data);
                root->right = cur;
            }

            return root;
        }
    }

    int height(Node* node, int lvl) {
        int l = 0;
        if (node->left) {
            l = height(node->left, lvl + 1);
        }

        int r = 0;
        if (node->right) {
            r = height(node->right, lvl + 1);
        }

        return max(lvl, max(l, r));
    }

    int height(Node* root) { return height(root, 0); }

    void clean(Node* node) {
        if (node->left) {
            clean(node->left);
            delete node->left;
        }

        if (node->right) {
            clean(node->right);
            delete node->right;
        }
    }

};  // End of Solution

TEST_CASE("tree height of a binary tree") {
    BinaryTree tree;
    Node* root = nullptr;
    for (int v : vector<int>{3, 1, 7, 5, 4}) {
        root = tree.insert(root, v);
    }

    REQUIRE(tree.height(root) == 3);

    tree.clean(root);
    delete root;
}
