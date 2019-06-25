// ex.3

// Given the root to a binary tree, implement serialize(root), which
// serializes the tree into a string, and deserialize(s), which
// deserializes the string back into the tree.

// For example, given the following Node class

// class Node:
//     def __init__(self, val, left=None, right=None):
//         self.val = val
//         self.left = left
//         self.right = right
// The following test should pass:

// node = Node('root', Node('left', Node('left.left')), Node('right'))
// assert deserialize(serialize(node)).left.left.val == 'left.left'

#include <catch2/catch.hpp>

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Node {
    Node(const string& v, Node* l = nullptr, Node* r = nullptr)
        : val{v}, left{l}, right{r} {}

    static void clean(Node* root) {
        if (root->left) {
            clean(root->left);
            root->left = nullptr;
        }
        if (root->right) {
            clean(root->right);
            root->right = nullptr;
        }

        delete root;
    }

    string val;
    Node* left = nullptr;
    Node* right = nullptr;
};

const char* nil = "nil";
const char* sep = " ";

string serialize(const Node* root, ostringstream& oss) {
    if (root) {
        oss << root->val << ' ';
        serialize(root->left, oss);
        serialize(root->right, oss);
    } else {
        oss << nil << ' ';
    }

    return oss.str();
}

string serialize(const Node* root) {
    ostringstream oss;
    return serialize(root, oss);
}

void deserialize(istringstream& iss, Node*& root) {
    if (!iss.eof()) {
        string val;
        iss >> val;

        if (val == nil) return;

        root = new Node(val);
        deserialize(iss, root->left);
        deserialize(iss, root->right);
    } else {
        root = nullptr;
    }
}

Node* deserialize(const string& s) {
    istringstream iss(s);
    Node* root = nullptr;
    deserialize(iss, root);
    return root;
}

TEST_CASE("ex.3") {
    Node* root = new Node("root", new Node("left", new Node("left.left")),
                          new Node("right"));

    Node* new_root = deserialize(serialize(root));
    REQUIRE(new_root->left->left->val == "left.left");

    Node::clean(root);
    Node::clean(new_root);
}
