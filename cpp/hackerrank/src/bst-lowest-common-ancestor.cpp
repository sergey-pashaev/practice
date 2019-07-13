// binary search tree: lowest common ancestor

// You are given pointer to the root of the binary search tree and two
// values v1 and v2. You need to return the lowest common ancestor
// (LCA) of v1 and v2 in the binary search tree.

// Function Description

// Complete the function lca in the editor below. It should return a pointer to
// the lowest common ancestor node of the two values given.

// lca has the following parameters:
// - root: a pointer to the root node of a binary search tree
// - v1: a node.data value
// - v2: a node.data value

#include <catch2/catch.hpp>

#include <vector>

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

    Node* lca(Node* root, int v1, int v2) {
        if (root->data > v1 && root->data > v2) {
            return lca(root->left, v1, v2);
        }

        if (root->data < v1 && root->data < v2) {
            return lca(root->right, v1, v2);
        }

        return root;
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
    for (int v : vector<int>{4, 2, 3, 1, 7, 6}) {
        root = tree.insert(root, v);
    }

    int v1 = 1;
    int v2 = 7;
    REQUIRE(tree.lca(root, v1, v2)->data == 4);

    tree.clean(root);
    delete root;
}
