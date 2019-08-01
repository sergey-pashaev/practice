// reverse a doubly linked list

// https://www.hackerrank.com/challenges/reverse-a-doubly-linked-list/problem

#include <catch2/catch.hpp>

using namespace std;

struct node {
    node(int d) : data{d} {}

    int data;
    node* next = nullptr;
    node* prev = nullptr;
};

node* reverse(node* head) {
    node* r = nullptr;
    node* c = head;
    node* n = head->next;
    while (c) {
        c->prev = c->next;
        c->next = r;

        r = c;
        c = n;
        if (n) n = n->next;
    }

    return r;
}

TEST_CASE("reverse a doubly linked list") {
    // TODO:
}
