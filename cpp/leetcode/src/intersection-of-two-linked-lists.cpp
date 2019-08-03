// intersection of two linked lists

// https://leetcode.com/problems/intersection-of-two-linked-lists/

#include <catch2/catch.hpp>

#include <set>

using namespace std;

struct node {
    node(int x) : val{x} {}

    int val;
    node *next = nullptr;
};

node *get_intersection_node(node *head_a, node *head_b) {
    if (!head_a || !head_b) return nullptr;

    set<node *> s;

    node *a = head_a;
    node *b = head_b;

    while (a || b) {
        if (a) {
            if (s.count(a)) return a;
            s.insert(a);
            a = a->next;
        }

        if (b) {
            if (s.count(b)) return b;
            s.insert(b);
            b = b->next;
        }
    }

    return nullptr;
}

TEST_CASE("intersection of two linked lists") {
    // TODO:
}
