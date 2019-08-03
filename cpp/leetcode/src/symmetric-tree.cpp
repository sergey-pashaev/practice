// symmetric tree

// https://leetcode.com/problems/symmetric-tree/

#include <catch2/catch.hpp>

#include <queue>

using namespace std;

struct node {
    node(int x) : val{x} {}

    int val;
    node* left = nullptr;
    node* right = nullptr;
};

bool is_symmetric(node* root) {
    queue<node*> q;
    q.push(root);
    q.push(root);

    while (!q.empty()) {
        node* n1 = q.front();
        q.pop();
        node* n2 = q.front();
        q.pop();

        if (!n1 && !n2) continue;
        if (!n1 || !n2) return false;
        if (n1->val != n2->val) return false;

        q.push(n1->left);
        q.push(n2->right);

        q.push(n1->right);
        q.push(n2->left);
    }

    return true;
}

TEST_CASE("symmetric tree") {}
