#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <memory>
#include <stdexcept>

namespace psv {

template <typename T>
class CircularBuffer {
   public:
    explicit CircularBuffer(std::size_t size)
        : n_{size + 1}, buf_{std::make_unique<T[]>(n_)}, r_{n_}, w_{0} {}

    bool Empty() const { return r_ % n_ == w_ % n_; }

    bool Full() const { return (w_ + 1) % n_ == r_ % n_; }

    std::size_t Size() const {
        if (w_ >= r_ % n_) {
            return w_ - (r_ % n_);
        } else {
            return (w_ + n_) - (r_ % n_);
        }
    }

    T Front() const {
        if (Empty()) Error("buffer is empty");
        return buf_[r_ % n_];
    }

    T Back() const {
        if (Empty()) Error("buffer is empty");
        return buf_[(w_ - 1) % n_];
    }

    void Write(T v) {
        if (Full()) {
            // advance read offset & forget oldest element
            r_ %= n_;
            r_++;
        }

        // advance write offset
        buf_[w_++] = v;
        w_ %= n_;
    }

    T Read() {
        if (Empty()) Error("buffer is empty");
        r_ %= n_;
        return buf_[r_++];
    }

   private:
    void Error(const char* msg) const { throw std::length_error(msg); }

   private:
    const std::size_t n_;
    std::unique_ptr<T[]> buf_;
    std::size_t r_ = 0;  // idx to read next item
    std::size_t w_ = 0;  // idx to write next item
};

}  // namespace psv

#endif /* CIRCULAR_BUFFER_H */
