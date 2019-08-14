#include <cstddef>

template <typename T>
class Array {
   public:
    explicit Array(size_t size = 0, const T& value = T())
        : size_(size), data_(size_ ? new T[size_] : 0) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

    Array(const Array& other)
        : size_(other.size_), data_(size_ ? new T[size_] : 0) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    ~Array() { delete[] data_; }

    Array& operator=(const Array<T>& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = size_ ? new T[size_] : 0;
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }

        return *this;
    }

    size_t size() const { return size_; }
    T& operator[](size_t i) { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

   private:
    size_t size_;
    T* data_;
};

int main() {}
