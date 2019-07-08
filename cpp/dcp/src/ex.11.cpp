// ex.11

// Implement an autocomplete system. That is, given a query string s
// and a set of all possible query strings, return all strings in the
// set that have s as a prefix.

// For example, given the query string de and the set of strings [dog,
// deer, deal], return [deer, deal].

// Hint: Try preprocessing the dictionary into a more efficient data
// structure to speed up queries.

#include <catch2/catch.hpp>

#include <set>

using namespace std;

// naive version
set<string> complete(const string& input, const set<string>& completions) {
    set<string> ret;

    for (const string& s : completions) {
        if (s.find(input) == 0) {
            ret.insert(s);
        }
    }

    return ret;
}

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

   private:
    Node* Contains(const std::string& key) {
        Node* node = root_;

        for (char c : key) {
            std::size_t idx = c - 'a';
            Node* next = node->children.at(idx);
            if (!next) {
                return nullptr;
            }

            node = next;
        }

        return node;
    }

    void AddKeys(const std::string& prefix, Node* node, set<string>& keys) {
        if (!node) return;

        if (node->end) {
            keys.insert(prefix);
        }

        for (std::size_t i = 0; i < alphabet_size; ++i) {
            if (node->children.at(i)) {
                char c = 'a' + i;
                AddKeys(prefix + static_cast<char>(c), node->children.at(i),
                        keys);
            }
        }
    }

   public:
    set<string> Suggest(const std::string& key) {
        Node* node = Contains(key);
        if (!node) return {};

        if (node->end) {
            return {key};
        }

        set<string> ret;
        AddKeys(key, node, ret);
        return ret;
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

// complete with trie
set<string> complete_trie(const string& input, const set<string>& completions) {
    Trie<26> trie;

    for (const string& s : completions) {
        trie.Insert(s);
    }

    return trie.Suggest(input);
}

TEST_CASE("ex.11") {
    set<string> completions = {"dog", "deer", "deal"};
    set<string> empty;

    REQUIRE(complete("de", completions) == set<string>({"deer", "deal"}));
    REQUIRE(complete_trie("de", completions) == set<string>({"deer", "deal"}));
    REQUIRE(complete_trie("x", completions) == empty);
}
