// linked list cycle

// https://leetcode.com/problems/linked-list-cycle/

#include <catch2/catch.hpp>

using namespace std;

struct node {
    node(int x) : val{x} {}

    int val;
    node* next = nullptr;
};

bool has_cycle(node* head) {
    if (!head) return false;
    node* slow = head;
    node* fast = head->next;

    while (slow != fast) {
        if (!fast || !fast->next) return false;
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}

TEST_CASE("linked list cycle") {
    // TODO:
}
