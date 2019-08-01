// ctci linked list cycle

// https://www.hackerrank.com/challenges/ctci-linked-list-cycle/problem

#include <catch2/catch.hpp>

using namespace std;

struct node {
    int data;
    node* next = nullptr;
};

bool has_cycle(node* head) {
    if (!head) return false;
    node* slow = head;
    node* fast = head->next;
    while (slow && fast) {
        if (slow == fast) return true;
        slow = slow->next;
        fast = fast->next;
        if (fast) fast = fast->next;
    }
    return false;
}

TEST_CASE("ctci linked list cycle") {
    // TODO:
}
