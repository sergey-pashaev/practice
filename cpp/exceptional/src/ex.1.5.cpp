// ex.1.5

// Обобщенные контейнеры с максимальным повторным
// использованием. Часть 2

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

    // copy ctor for same size only
    fixed_vector(const fixed_vector& other) = default;

    // assignment for same size only
    fixed_vector& operator=(const fixed_vector& other) = default;

    // "copy ctor" for different sizes (not a copy ctor, since T != U)
    template <typename U, std::size_t osize>
    fixed_vector(const fixed_vector<U, osize>& other) {
        std::copy(other.begin(), other.begin() + std::min(size, osize),
                  begin());
    }

    // "assignment" for different sizes (not a assignment, since T != U)
    template <typename U, std::size_t osize>
    fixed_vector& operator=(const fixed_vector<U, osize>& other) {
        std::copy(other.begin(), other.begin() + std::min(size, osize),
                  begin());
        return *this;
    }

    // "copy ctor" STL-style
    template <typename RandomAccessIterator>
    fixed_vector(RandomAccessIterator first, RandomAccessIterator last) {
        std::copy(
            first,
            first + std::min(size, static_cast<std::size_t>(last - first)),
            begin());
    }

    // "assignment" STL-style
    template <typename RandomAccessIterator>
    fixed_vector& assign(RandomAccessIterator first,
                         RandomAccessIterator last) {
        std::copy(
            first,
            first + std::min(size, static_cast<std::size_t>(last - first)),
            begin());
        return *this;
    }

    iterator begin() { return v_; }
    iterator end() { return v_ + size; }
    const_iterator begin() const { return v_; }
    const_iterator end() const { return v_ + size; }

   private:
    T v_[size];
};

TEST_CASE("copy ctor same size") {
    fixed_vector<int, 3> v1;
    fixed_vector<int, 3> v2(v1);

    REQUIRE(std::equal(v1.begin(), v1.end(), v2.begin()));
}

TEST_CASE("copy ctor other size") {
    fixed_vector<int, 5> v1;
    fixed_vector<int, 3> v2(v1);
    fixed_vector<int, 7> v3(v1);

    REQUIRE(std::equal(v2.begin(), v2.end(), v1.begin()));
    REQUIRE(std::equal(v1.begin(), v1.end(), v3.begin()));
}

TEST_CASE("assignment same size") {
    fixed_vector<int, 3> v1;
    fixed_vector<int, 3> v2 = v1;

    REQUIRE(std::equal(v1.begin(), v1.end(), v2.begin()));
}

TEST_CASE("assignment other size") {
    fixed_vector<int, 5> v1;
    fixed_vector<int, 3> v2(v1);
    fixed_vector<int, 7> v3(v1);

    REQUIRE(std::equal(v2.begin(), v2.end(), v1.begin()));
    REQUIRE(std::equal(v1.begin(), v1.end(), v3.begin()));
}

TEST_CASE("different types wide -> narrow") {
    fixed_vector<int, 3> v1;
    fixed_vector<char, 3> v2 = v1;

    REQUIRE(!std::equal(v2.begin(), v2.end(), v1.begin()));
}

TEST_CASE("different types narrow -> wide") {
    fixed_vector<char, 3> v1;
    fixed_vector<int, 3> v2 = v1;

    REQUIRE(std::equal(v2.begin(), v2.end(), v1.begin()));
}

// exception safe variant
template <typename T, std::size_t size>
class safe_fixed_vector {
   public:
    using iterator = T*;
    using const_iterator = const T*;

    safe_fixed_vector() : v_{new T[size]} {}
    ~safe_fixed_vector() { delete[] v_; }

    void Swap(safe_fixed_vector<T, size>& other) noexcept {
        swap(v_, other.v_);
    }

    // "copy ctor" for different sizes (not a copy ctor, since T != U)
    template <typename U, std::size_t osize>
    safe_fixed_vector(const safe_fixed_vector<U, osize>& other)
        : v_{new T[size]} {
        try {
            std::copy(other.begin(), other.begin() + std::min(size, osize),
                      begin());
        } catch (...) {
            delete[] v_;
        }
    }

    // "assignment" for different sizes (not a assignment, since T != U)
    template <typename U, std::size_t osize>
    safe_fixed_vector& operator=(const safe_fixed_vector<U, osize>& other) {
        safe_fixed_vector<T, size> tmp(other);
        Swap(tmp);
        return *this;
    }

    iterator begin() { return v_; }
    iterator end() { return v_ + size; }
    const_iterator begin() const { return v_; }
    const_iterator end() const { return v_ + size; }

   private:
    T* v_;
};
