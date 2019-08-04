
namespace psv {

class BinarySearchTree {
   private:
    struct Node {
        Node(int d) : data{d} {}

        int data;
        Node* l = nullptr;
        Node* r = nullptr;
    };

    using Link = Node*;

   public:
    BinarySearchTree() = default;

    ~BinarySearchTree() {
        if (root_) {
            Clean(root_);
            delete root_;
            root_ = nullptr;
        }
    }

    void Insert(int data) { Insert(root_, data); }

    template <typename Func>
    void Traverse(Func f) {
        Traverse(root_, 0, f);
    }

   private:
    template <typename Func>
    void Traverse(Link node, int lvl, Func f) {
        if (!node) return;

        f(lvl, node->data);  // top down
        Traverse(node->l, lvl + 1, f);
        // by level
        Traverse(node->r, lvl + 1, f);
        // bottom up
    }

    void Insert(Link& node, int data) {
        if (!node) {
            node = new Node(data);
            return;
        }

        if (data < node->data) {
            Insert(node->l, data);
        } else {
            Insert(node->r, data);
        }
    }

    void Clean(Link node) {
        if (node->l) {
            Clean(node->l);
            delete node->l;
            node->l = nullptr;
        }

        if (node->r) {
            Clean(node->r);
            delete node->r;
            node->r = nullptr;
        }
    }

   private:
    Link root_ = nullptr;
};

}  // namespace psv
