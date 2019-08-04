// remove nth node from end of list

// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

#include <catch2/catch.hpp>

using namespace std;

struct node {
    node(int x) : val{x} {}

    int val;
    node* next = nullptr;
};

bool next_n_empty(node* head, int n) {
    node* curr = head;
    while (curr && n > 0) {
        curr = curr->next;
        --n;
    }

    return n == 0 && curr == nullptr;
}

node* remove_nth_from_end(node* head, int n) {
    node* prev = nullptr;
    node* curr = head;

    while (curr) {
        if (next_n_empty(curr, n)) {
            node* next = curr->next;
            if (prev) {
                prev->next = curr->next;
            } else {
                head = next;
            }
            delete curr;
            break;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    return head;
}

TEST_CASE("remove nth node from end of list") {
    // TODO:
}
