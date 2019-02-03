#ifndef PSV_VECTOR_H
#define PSV_VECTOR_H

#include <algorithm>
#include <stdexcept>

namespace psv {

template <typename T>
class Vector {
   public:
    explicit Vector(int capacity = 16)
        : data_{capacity ? new T[capacity] : nullptr},
          capacity_{capacity},
          size_{0} {}

    Vector(const Vector& other)
        : data_{other.capacity_ ? new T[other.capacity_] : nullptr},
          capacity_{other.capacity_},
          size_{other.size_} {
        std::copy(other.data_, other.data_ + capacity_, data_);
    }

    Vector(Vector&& other) : Vector(0) { swap(*this, other); }

    ~Vector() { delete[] data_; }

    Vector& operator=(Vector other) {
        // Pass other as value to make a copy and swap it with this.
        swap(*this, other);
        return *this;
    }

    friend void swap(Vector& lhs, Vector& rhs) noexcept {
        using std::swap;
        swap(lhs.data_, rhs.data_);
        swap(lhs.capacity_, rhs.capacity_);
        swap(lhs.size_, rhs.size_);
    }

    int Size() const { return size_; }

    int Capacity() const { return capacity_; }

    bool IsEmpty() const { return size_ == 0; }

    T& At(int index) {
        if (index >= size_ || index < 0) ThrowOutOfRange();
        return data_[index];
    }

    const T& At(int index) const {
        if (index >= size_ || index < 0) ThrowOutOfRange();
        return data_[index];
    }

    void PushBack(T v) {
        if (size_ == capacity_) Increase();
        data_[size_++] = v;
    }

    void Insert(int index, T v) {
        if (index > size_ || index < 0) ThrowOutOfRange();
        if (size_ + 1 == capacity_) Increase();

        for (int i = size_ - 1; i >= index; --i) {
            data_[i + 1] = data_[i];
        }

        data_[index] = v;
        ++size_;
    }

    void Delete(int index) {
        if (index > size_ - 1 || index < 0) ThrowOutOfRange();

        for (int i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }

        --size_;
    }

    void Reserve(int capacity) {
        if (capacity <= capacity_) return;

        T* data = new T[capacity];
        std::copy(data_, data_ + capacity_, data);
        std::swap(data_, data);
        capacity_ = capacity;
        delete[] data;
    }

   private:
    void ThrowOutOfRange() const {
        throw std::out_of_range("index out of range");
    }

    void Increase() { Reserve(capacity_ * 2); }

   private:
    T* data_;
    int capacity_;
    int size_;
};

}  // namespace psv

#endif /* PSV_VECTOR_H */
