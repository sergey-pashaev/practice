#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <math.h>
#include <array>
#include <stdexcept>
#include <vector>

namespace psv {

template <typename T>
class Heap {
   public:
    explicit Heap(int size) : size_(0), data_(size + 1) {}

    const T& At(int n) const { return data_.at(n); }

    int Root() const { return 1; }

    // Return index of parent node, 0 - if n is root
    int Parent(int n) {
        if (n == Root()) return 0;
        return n / 2;
    }

    // Return index of left child element of n node
    int Child(int n) { return 2 * n; }

    // Insert value to right place in heap
    void Insert(T value) {
        if (size_ > data_.size() - 1) {
            throw std::out_of_range("heap is full");
        }

        ++size_;
        data_[size_] = value;
        BubbleUp(size_);
    }

    // Remote root element & heapify tree
    T ExtractRoot() {
        if (size_ <= 0) {
            throw std::out_of_range("heap is empty");
        }

        T min = data_.at(Root());
        data_.at(Root()) = data_.at(size_ - 1);
        --size_;
        data_.resize(data_.size() - 1);
        BubbleDown(Root());
        return min;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Heap<U>& heap);

   private:
    // Make sure nth element is dominated by its parent
    void BubbleUp(int n) {
        if (n == Root()) return;

        const int parent = Parent(n);
        if (data_.at(parent) > data_.at(n)) {
            std::swap(data_.at(parent), data_.at(n));
            BubbleUp(parent);
        }
    }

    // Make sure nth element is dominating its children
    void BubbleDown(int n) {
        // find minimum of childrent
        int min = n;  // current element
        for (int i = 0; i < 2; ++i) {
            const int child = Child(n) + i;
            if (child < size_ && data_.at(child) < data_.at(min)) {
                min = child;
            }
        }

        if (min != n) {
            // some child is lesser than nth element
            std::swap(data_.at(min), data_.at(n));
            BubbleDown(min);
        }
    }

   private:
    int size_;
    std::vector<T> data_;
};

template <typename U>
std::ostream& operator<<(std::ostream& os, const Heap<U>& heap) {
    int level = 1;
    for (int i = 1; i <= heap.size_; ++i) {
        os << heap.data_.at(i) << ' ';

        if (i == std::pow(2, level) - 1) {
            ++level;
            os << '\n';
        }
    }
    os << '\n';
    return os;
}

}  // namespace psv

#endif /* HEAPSORT_H */
