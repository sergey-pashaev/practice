#include <array>
#include <string>

namespace psv {

template <std::size_t alphabet_size>
class Trie {
   private:
    struct Node {
        std::array<Node*, alphabet_size> children = {};
        bool end = false;
    };

   public:
    Trie() : root_{new Node()} {}

    ~Trie() {
        if (root_) {
            Clean(root_);
        }
    }

    void Insert(const std::string& key) {
        Node* node = root_;

        for (char c : key) {
            std::size_t idx = c - 'a';
            Node* next = node->children.at(idx);
            if (next == nullptr) {
                node->children.at(idx) = new Node();
                next = node->children.at(idx);
            }

            node = next;
        }

        node->end = true;
    }

    bool Lookup(const std::string& key) {
        Node* node = root_;

        for (char c : key) {
            std::size_t idx = c - 'a';
            Node* next = node->children.at(idx);
            if (!next) {
                return false;
            }

            node = next;
        }

        return node && node->end;
    }

   private:
    void Clean(Node* node) {
        for (Node* child : node->children) {
            if (child) {
                Clean(child);
            }
        }

        delete node;
        node = nullptr;
    }

   private:
    Node* root_;
};

}  // namespace psv
