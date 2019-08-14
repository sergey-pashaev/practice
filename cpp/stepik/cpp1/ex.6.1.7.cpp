#include <cstddef>

template <typename T>
class Array {
   public:
    Array(size_t size, const T& value)
        : size_(size), data_(size ? (T*)new char[size_ * sizeof(T)] : 0) {
        for (size_t i = 0; i < size_; ++i) {
            new (data_ + i) T(value);
        }
    }

    Array() : size_(0), data_(0) {}

    Array(const Array<T>& other)
        : size_(other.size_),
          data_(size_ ? (T*)new char[size_ * sizeof(T)] : 0) {
        copy(other);
    }

    ~Array() { del(); }

    Array& operator=(const Array<T>& other) {
        if (this != &other) {
            del();

            size_ = other.size_;
            data_ = size_ ? (T*)new char[size_ * sizeof(T)] : 0;

            copy(other);
        }

        return *this;
    }

    size_t size() const { return size_; }
    T& operator[](size_t i) { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

   private:
    void copy(const Array<T>& other) {
        for (size_t i = 0; i < size_; ++i) {
            new (data_ + i) T(other.data_[i]);
        }
    }

    void del() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        delete[](char*) data_;
    }

   private:
    size_t size_;
    T* data_;
};

int main() {}
