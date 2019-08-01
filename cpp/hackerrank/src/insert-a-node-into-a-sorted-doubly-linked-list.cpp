// insert a node into a sorted doubly linked list

// https://www.hackerrank.com/challenges/insert-a-node-into-a-sorted-doubly-linked-list/problem

#include <catch2/catch.hpp>

using namespace std;
struct node {
    node(int d) : data{d} {}

    int data;
    node* next = nullptr;
    node* prev = nullptr;
};

node* sorted_insert(node* head, int data) {
    node* n = new node(data);
    if (!head) return n;

    node* curr = head;
    node* prev = nullptr;
    while (curr) {
        if (curr->data >= data) {
            n->next = curr;
            n->prev = prev;
            if (prev) {
                prev->next = n;
                curr->prev = n;
            } else {
                curr->prev = n;
                head = n;
            }
            return head;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    if (prev) {
        prev->next = n;
        n->prev = prev;
    }

    return head;
}

TEST_CASE("insert a node into a sorted doubly linked list") {
    // TODO:
}
