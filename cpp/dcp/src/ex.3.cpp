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

string serialize(const Node& n, int lvl, string& acc) {
    acc += to_string(lvl) + ':' + n.val + ' ';
    if (n.left) serialize(*n.left, lvl + 1, acc);
    if (n.right) serialize(*n.right, lvl + 1, acc);
    return acc;
}

string serialize(const Node& root) {
    string acc;
    return serialize(root, 0, acc);
}

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    istringstream ss(s);
    for (string token; getline(ss, token, delimiter);) {
        tokens.push_back(token);
    }
    return tokens;
}

Node* deserialize(const vector<string>& vs) {
    for (auto& s : vs) {
        cout << s;
    }
    return nullptr;
}

Node* deserialize(const vector<string>& vs, Node* prev) {}

TEST_CASE("ex.3") {
    Node* root = new Node("root", new Node("left", new Node("left.left")),
                          new Node("right"));

    cout << serialize(*root) << '\n';
    Node::clean(root);
}
