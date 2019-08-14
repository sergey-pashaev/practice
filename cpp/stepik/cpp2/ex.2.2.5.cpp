#include <cstddef>
#include <utility>

template <class T>
struct Array {
    // все объявленные ниже методы уже реализованы
    explicit Array(size_t size = 0);
    Array(Array const& a);
    Array& operator=(Array const& a);
    ~Array();

    size_t size() const;
    T& operator[](size_t i);
    T const& operator[](size_t i) const;

    void swap(Array& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

    // реализуйте перемещающий конструктор
    Array(Array&& other) : Array() { swap(other); }

    // реализуйте перемещающий оператор присваивания
    Array& operator=(Array&& other) {
        swap(other);
        return *this;
    }

   private:
    size_t size_;
    T* data_;
};

int main() {}
