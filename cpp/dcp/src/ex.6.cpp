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
        // TODO:
    }

    Node* Next(Node* node, Node* prev) {
        Node* ret = nullptr;
        if (node->both) {
            ret = (Node*)(uintptr_t(prev) ^ node->both);
        }
        return ret;
    }

    Node* Prev(Node* node, Node* next) {
        Node* ret = nullptr;
        if (node->both) {
            ret = (Node*)(uintptr_t(next) ^ node->both);
        }
        return ret;
    }

    void Add(Node* node) {
        if (!head) {
            head = node;
            return;
        } else {
            Node* cur = head;
            Node* prev = nullptr;
            Node* next = Next(cur, prev);
            while (next) {
                prev = cur;
                cur = next;
                next = Next(cur, prev);
            }

            cur->both = uintptr_t(prev) ^ uintptr_t(node);
            node->both = uintptr_t(cur) ^ uintptr_t(next);
        }
    }

    Node* Get(size_t n) {
        if (!head) return nullptr;
        size_t i = 0;
        Node* cur = head;
        if (i == n) return cur;
        Node* prev = nullptr;
        Node* next = Next(cur, prev);
        while (next) {
            prev = cur;
            cur = next;
            ++i;
            if (i == n) return cur;
            next = Next(cur, prev);
        }
        return nullptr;
    }

    void Print() {
        if (!head) return;
        Node* cur = head;
        cout << cur->v << "\n";
        Node* prev = nullptr;
        Node* next = Next(cur, prev);
        while (next) {
            prev = cur;
            cur = next;
            cout << cur->v << "\n";
            next = Next(cur, prev);
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
