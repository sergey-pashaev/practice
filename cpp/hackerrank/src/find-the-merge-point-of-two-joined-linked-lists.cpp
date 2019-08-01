// find the merge point of two joined linked lists

// https://www.hackerrank.com/challenges/find-the-merge-point-of-two-joined-linked-lists/problem

#include <catch2/catch.hpp>

#include <set>

using namespace std;

struct node {
    node(int d) : data{d} {}

    int data;
    node* next = nullptr;
};

int find_merge_node(node* head1, node* head2) {
    node* a = head1;
    node* b = head2;
    set<node*> seen;

    while (a || b) {
        if (a) {
            if (seen.count(a)) return a->data;
            seen.insert(a);
            a = a->next;
        }

        if (b) {
            if (seen.count(b)) return b->data;
            seen.insert(b);
            b = b->next;
        }
    }

    return -1;
}

TEST_CASE("find the merge point of two joined linked lists") {
    // TODO:
}
