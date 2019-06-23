// ex.1.4

// Обобщенные контейнеры с максимальным повторным
// использованием. Часть 1

#include <algorithm>
#include <cstddef>

#include <catch2/catch.hpp>

using namespace std;

template <typename T, std::size_t size>
class fixed_vector {
   public:
    using iterator = T*;
    using const_iterator = const T*;

    fixed_vector() = default;

    // works for same size only
    fixed_vector(const fixed_vector& other) {
        std::copy(other.begin(), other.end(), begin());
    }

    // works for same size only
    fixed_vector& operator=(const fixed_vector& other) {
        std::copy(other.begin(), other.end(), begin());
        return *this;
    }

    iterator begin() { return v_; }
    iterator end() { return v_ + size; }
    const_iterator begin() const { return v_; }
    const_iterator end() const { return v_ + size; }

   private:
    T v_[size];
};

TEST_CASE("copy ctor") {
    fixed_vector<int, 3> v1;
    fixed_vector<int, 3> v2(v1);

    REQUIRE(std::equal(v1.begin(), v1.end(), v2.begin()));
}

TEST_CASE("assignment") {
    fixed_vector<int, 3> v1;
    fixed_vector<int, 3> v2 = v1;

    REQUIRE(std::equal(v1.begin(), v1.end(), v2.begin()));
}
