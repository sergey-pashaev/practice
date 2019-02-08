#ifndef PSV_LIST_H
#define PSV_LIST_H

#include <cstddef>
#include <stdexcept>

namespace psv {

template <typename T>
class LinkedList {
   public:
    struct Node {
        Node() : v{}, next{nullptr} {}
        Node(T v, Node* next = nullptr) : v{v}, next{next} {}

        T v;
        Node* next;
    };

    LinkedList() : head_{nullptr} {}

    LinkedList(const LinkedList& other) : head_{nullptr} {
        Node* tail = nullptr;
        for (Node* cur = other.head_; cur; cur = cur->next) {
            Node* t = new Node(cur->v);
            if (tail) {
                tail->next = t;
            }
            tail = t;

            if (!head_) head_ = tail;
        }
    }

    LinkedList(LinkedList&& other) : LinkedList{} { swap(*this, other); }

    ~LinkedList() {
        Node* cur = head_;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    LinkedList& operator=(LinkedList other) {
        // Pass other as value to make a copy and swap it with this.
        swap(*this, other);
        return *this;
    }

    friend void swap(LinkedList& lhs, LinkedList& rhs) noexcept {
        using std::swap;
        swap(lhs.head_, rhs.head_);
    }

    std::size_t Size() const {
        std::size_t count = 0;
        for (Node* cur = head_; cur; cur = cur->next) {
            ++count;
        }

        return count;
    }

    bool IsEmpty() const { return head_ == nullptr; }

    T& At(std::size_t index) {
        std::size_t i = 0;
        for (Node* cur = head_; cur; cur = cur->next, ++i) {
            if (i == index) return cur->v;
        }

        ThrowOutOfRange();
    }

    T& At(std::size_t index) const {
        std::size_t i = 0;
        for (const Node* cur = head_; cur; cur = cur->next, ++i) {
            if (i == index) return cur->v;
        }

        ThrowOutOfRange();
    }

    void PushBack(T v) {
        if (IsEmpty()) {
            head_ = new Node(v);
            return;
        }

        Node* cur = head_;
        while (cur && cur->next) {
            cur = cur->next;
        }

        cur->next = new Node(v);
    }

    void PushFront(T v) {
        if (IsEmpty()) {
            head_ = new Node();
            return;
        }

        Node* t = new Node(v);
        t->next = head_;
        head_ = t;
    }

    T PopBack() {
        if (IsEmpty()) ThrowEmptyList();

        Node* cur = head_;
        while (cur && cur->next && cur->next->next) cur = cur->next;

        Node* last = cur->next;
        T v = last->v;
        delete last;
        cur->next = nullptr;
        return v;
    }

    T PopFront() {
        if (IsEmpty()) ThrowEmptyList();

        T v = head_->v;
        Node* next = head_->next;
        delete head_;
        head_ = next;
        return v;
    }

    T Back() const {
        if (IsEmpty()) ThrowEmptyList();

        Node* cur = head_;
        while (cur && cur->next) {
            cur = cur->next;
        }

        return cur->v;
    }

    T Front() const {
        if (IsEmpty()) ThrowEmptyList();

        return head_->v;
    }

    void Insert(std::size_t index, T v) {
        std::size_t i = 0;
        for (Node *cur = head_, *prev = nullptr; cur;
             prev = cur, cur = cur->next, ++i) {
            if (i == index) {
                Node* t = new Node(v);
                if (prev) {
                    prev->next = t;
                    t->next = cur;
                } else {
                    head_ = t;
                    head_->next = cur;
                }
                return;
            }
        }

        ThrowOutOfRange();
    }

    void Remove(std::size_t index) {
        std::size_t i = 0;
        for (Node *cur = head_, *prev = nullptr; cur;
             prev = cur, cur = cur->next, ++i) {
            if (i == index) {
                Node* next = cur->next;
                delete cur;
                if (prev) {
                    prev->next = next;
                } else {
                    head_ = next;
                }
                return;
            }
        }

        ThrowOutOfRange();
    }

    void RemoveValue(T v) {
        for (Node *cur = head_, *prev = nullptr; cur;
             prev = cur, cur = cur->next) {
            if (cur->v == v) {
                Node* next = cur->next;
                delete cur;
                if (prev) {
                    prev->next = next;
                } else {
                    head_ = next;
                }
                return;
            }
        }
    }

    void Reverse() {
        Node* tail = nullptr;
        Node* cur = head_;
        Node* next = nullptr;
        while (cur) {
            next = cur->next;
            if (tail) {
                cur->next = tail;
                tail = cur;
            } else {
                tail = cur;
                tail->next = nullptr;
            }

            cur = next;
        }

        head_ = tail;
    }

   private:
    void ThrowOutOfRange() const {
        throw std::out_of_range("index out of range");
    }

    void ThrowEmptyList() const { throw std::out_of_range("list is empty"); }

   private:
    Node* head_;
};

}  // namespace psv

#endif /* PSV_LIST_H */
