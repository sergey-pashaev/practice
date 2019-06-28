// ex.6

// An XOR linked list is a more memory efficient doubly linked
// list. Instead of each node holding next and prev fields, it holds a
// field named both, which is an XOR of the next node and the previous
// node. Implement an XOR linked list; it has an add(element) which
// adds the element to the end, and a get(index) which returns the
// node at index.

// If using a language that has no pointers (such as Python), you can
// assume you have access to get_pointer and dereference_pointer
// functions that converts between nodes and memory addresses.

#include <catch2/catch.hpp>

#include <cstdint>
#include <iostream>

using namespace std;

struct Node {
    Node(int v) : v{v} {}
    int v = 0;
    uintptr_t both = 0;
};

struct XorList {
    Node* head = nullptr;

    XorList() = default;

    ~XorList() {
        Node* curr = head;
        Node* prev = nullptr;
        Node* next = nullptr;
        while (curr) {
            next = Next(curr, prev);
            prev = curr;

            delete curr;
            curr = next;
        }
    }

    Node* Next(Node* curr, Node* prev) {
        Node* ret = nullptr;
        if (curr && curr->both) {
            ret = (Node*)(uintptr_t(prev) ^ curr->both);
        }
        return ret;
    }

    Node* Prev(Node* curr, Node* next) {
        Node* ret = nullptr;
        if (curr && curr->both) {
            ret = (Node*)(uintptr_t(next) ^ curr->both);
        }
        return ret;
    }

    void Add(Node* node) {
        if (!head) {
            head = node;
            return;
        } else {
            Node* curr = head;
            Node* prev = nullptr;
            Node* next = Next(curr, prev);
            while (next) {
                prev = curr;
                curr = next;
                next = Next(curr, prev);
            }

            curr->both = uintptr_t(prev) ^ uintptr_t(node);
            node->both = uintptr_t(curr) ^ uintptr_t(next);
        }
    }

    Node* Get(size_t n) {
        size_t i = 0;
        Node* curr = head;
        Node* prev = nullptr;
        Node* next = nullptr;
        while (curr) {
            if (i++ == n) return curr;

            next = Next(curr, prev);
            prev = curr;
            curr = next;
        }

        return nullptr;
    }

    void Print() {
        Node* curr = head;
        Node* prev = nullptr;
        Node* next = nullptr;
        while (curr) {
            cout << curr->v << '\n';

            next = Next(curr, prev);
            prev = curr;
            curr = next;
        }
    }
};

TEST_CASE("ex.6") {
    XorList list;
    Node* n0 = new Node(5);
    Node* n1 = new Node(9);
    Node* n2 = new Node(13);
    Node* n3 = new Node(15);

    list.Add(n0);
    list.Add(n1);
    list.Add(n2);
    list.Add(n3);

    list.Print();

    REQUIRE(n0 == list.Get(0));
    REQUIRE(n1 == list.Get(1));
    REQUIRE(n2 == list.Get(2));
    REQUIRE(n3 == list.Get(3));
}
