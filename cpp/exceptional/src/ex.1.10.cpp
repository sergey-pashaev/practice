// ex.1.10

// Предикаты. Часть 2

#include <algorithm>
#include <functional>
#include <vector>

#include <catch2/catch.hpp>

using namespace std;

// example of predicate with const values
template <typename T>
class GreaterThan : public unary_function<T, bool> {
   public:
    GreaterThan(T value) : v_{value} {}

    bool operator()(const T& t) const { return t > v_; }

   private:
    const T v_;
};

TEST_CASE("GreaterThan") {
    vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8};

    REQUIRE(find_if(vi.begin(), vi.end(), GreaterThan(5)) != vi.end());
    REQUIRE(find_if(vi.begin(), vi.end(), GreaterThan(10)) == vi.end());
}

// example of predicate with state
class FlagNth {
   public:
    FlagNth(std::size_t n) : current_{0}, n_{n} {}

    template <typename T>
    bool operator()(const T&) {
        return ++current_ == n_;
    }

   private:
    std::size_t current_;
    const std::size_t n_;
};

TEST_CASE("FlagNth") {
    vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8};

    // not reliable to use statefull predicate with STL, since it
    // might be copied & the order of applying of predicate to
    // elements of sequence is not defined
    REQUIRE(*find_if(vi.begin(), vi.end(), FlagNth(5)) == 5);
}
