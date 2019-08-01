// insert a node at a specific position in a linked list

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

struct node {
    node(int d) : data{d} {}

    int data;
    node* next = nullptr;
};

node* insert_node_at_position(node* head, int data, int position) {
    node* prev = nullptr;
    node* curr = head;
    while (position-- && curr->next) {
        prev = curr;
        curr = curr->next;
    }

    node* n = new node(data);
    if (prev) prev->next = n;
    n->next = curr;

    return head;
}

TEST_CASE("insert a node at a specific position in a linked list") {
    // TODO:
}
