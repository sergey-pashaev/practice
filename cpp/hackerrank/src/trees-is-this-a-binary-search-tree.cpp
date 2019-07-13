// trees: is this a binary search tree?

// For the purposes of this challenge, we define a binary search tree
// to be a binary tree with the following properties:

// The data value of every node in a node's left subtree is less than
// the data value of that node.

// The data value of every node in a node's right subtree is greater
// than the data value of that node.

// The data value of every node is distinct.

// Given the root node of a binary tree, determine if it is a binary
// search tree.

// Function Description

// Complete the function checkBST in the editor below. It must return
// a boolean denoting whether or not the binary tree is a binary
// search tree.

// checkBST has the following parameter(s):

// root: a reference to the root node of a tree to test

#include <catch2/catch.hpp>

#include <limits>

using namespace std;

struct Node {
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

    bool is_valid(Node* root) {
        return is_valid(root, numeric_limits<int>::min(),
                        numeric_limits<int>::max());
    }

    bool is_valid(Node* root, int min, int max) {
        if (!root) return true;

        if (root->data <= min || root->data >= max) {
            return false;
        }

        return is_valid(root->left, min, root->data) &&
               is_valid(root->right, root->data, max);
    }

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
};

TEST_CASE("bst-lowest-common-ancestor") {
    BinaryTree tree;
    Node* root = nullptr;
    for (int v : vector<int>{1, 2, 4, 3, 5, 6, 7}) {
        root = tree.insert(root, v);
    }

    REQUIRE(tree.is_valid(root));

    tree.clean(root);
    delete root;
}
