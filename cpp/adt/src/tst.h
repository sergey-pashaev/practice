#ifndef PSV_TST_H
#define PSV_TST_H

#include <string>

namespace psv {

class TernarySearchTree {
   private:
    struct Node {
        Node(int d) : data{d} {}

        int data;
        bool end = false;
        Node* lt = nullptr;
        Node* eq = nullptr;
        Node* gt = nullptr;
    };

    using Link = Node*;

   public:
    TernarySearchTree() = default;
    ~TernarySearchTree() {
        if (root_) {
            Clean(root_);
            delete root_;
        }
    }

    void Clean(Link node) {
        if (node->lt) {
            Clean(node->lt);
            delete node->lt;
        }

        if (node->gt) {
            Clean(node->gt);
            delete node->gt;
        }

        if (node->eq) {
            Clean(node->eq);
            delete node->eq;
        }
    }

    bool Search(const std::string& key) { return SearchR(key, 0, root_); }

    void Insert(const std::string& key) { InsertR(key, 0, root_); }

   private:
    static const int eok = -1;  // end of key

    int digit(const std::string& key, std::size_t pos) {
        return pos == key.size() ? eok : key[pos];
    }

    bool SearchR(const std::string& key, std::size_t pos, Link node) {
        int i = digit(key, pos);
        if (!node) {
            return false;
        }

        if (i == eok) {
            return node->end;
        }

        if (i < node->data) {
            return SearchR(key, pos, node->lt);
        } else if (i > node->data) {
            return SearchR(key, pos, node->gt);
        } else {
            return SearchR(key, pos + 1, node->eq);
        }
    }

    void InsertR(const std::string& key, std::size_t pos, Link& node) {
        int i = digit(key, pos);
        if (node == nullptr) {
            node = new Node(i);
        }

        if (i == eok) {
            node->end = true;
            return;
        }

        if (i < node->data) {
            InsertR(key, pos, node->lt);
        } else if (i == node->data) {
            InsertR(key, pos + 1, node->eq);
        } else {
            InsertR(key, pos, node->gt);
        }
    }

   private:
    Link root_ = nullptr;
};

}  // namespace psv

#endif /* PSV_TST_H */
