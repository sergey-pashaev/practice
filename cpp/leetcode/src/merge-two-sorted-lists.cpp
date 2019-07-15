// merge two sorted lists

// https://leetcode.com/problems/merge-two-sorted-lists/

// Merge two sorted linked lists and return it as a new list. The new
// list should be made by splicing together the nodes of the first two
// lists.

// Example:

// Input: 1->2->4, 1->3->4
// Output: 1->1->2->3->4->4

#include <catch2/catch.hpp>

#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* chose(ListNode* a, ListNode* b) {
    if (!a && !b) return nullptr;
    if (!a) return b;
    if (!b) return a;
    return a->val < b->val ? a : b;
}

ListNode* merge(ListNode* a, ListNode* b) {
    ListNode* sorted = chose(a, b);
    ListNode* node = sorted;
    while (node) {
        if (a == node) {
            a = a->next;
        }
        if (b == node) {
            b = b->next;
        }

        node->next = chose(a, b);
        node = node->next;
    }

    return sorted;
}

#include <iostream>

TEST_CASE("merge two sorted lists") {
    ListNode l1[3] = {ListNode(1), ListNode(2), ListNode(3)};
    l1[0].next = &l1[1];
    l1[1].next = &l1[2];

    ListNode l2[3] = {ListNode(1), ListNode(3), ListNode(4)};
    l2[0].next = &l2[1];
    l2[1].next = &l2[2];

    ListNode* sorted = merge(&l1[0], &l2[0]);
    ListNode* n = sorted;
    while (n) {
        cout << n->val << '\n';
        n = n->next;
    }
}
