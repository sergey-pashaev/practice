// add two numbers

// https://leetcode.com/problems/add-two-numbers/

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

struct node {
    node(int v) : val{v} {}

    int val;
    node* next = nullptr;
};

node* add(node* n1, node* n2, int& c) {
    int a = n1 ? n1->val : 0;
    int b = n2 ? n2->val : 0;
    int v = a + b + c;
    if (v > 9) {
        c = 1;
        v = v % 10;
    } else {
        c = 0;
    }
    return new node(v);
}

node* add_two_numbers(node* l1, node* l2) {
    node* ret = nullptr;
    node* cur = nullptr;
    int c = 0;
    while (l1 || l2 || c) {
        if (!ret) {
            ret = add(l1, l2, c);
            cur = ret;
        } else {
            cur->next = add(l1, l2, c);
            cur = cur->next;
        }

        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    return ret;
}

TEST_CASE("add two numbers") {
    // TODO:
}
