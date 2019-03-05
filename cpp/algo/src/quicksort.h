#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>

namespace psv {

template <typename T>
int partition(std::vector<T>& v, int lo, int hi) {
    int pivot = hi;
    int first_hi = lo;  // index of first element which higher than pivot

    // go up to pivot and swap all elements which lesser than pivot
    // with ones which greater than pivot & keep track of index of
    // first element which greater than pivot, so all elements in the
    // beginning is lesser than pivot
    for (int i = lo; i < hi; ++i) {
        if (v[i] < v[pivot]) {
            std::swap(v[i], v[first_hi++]);
        }
    }

    std::swap(v[pivot], v[first_hi]);
    return first_hi;
}

template <typename T>
void quicksort(std::vector<T>& v, int lo, int hi) {
    if (lo < hi) {
        int p = partition(v, lo, hi);
        quicksort(v, lo, p - 1);
        quicksort(v, p + 1, hi);
    }
}

template <typename T>
void quicksort(std::vector<T>& v) {
    quicksort(v, 0, v.size() - 1);
}

}  // namespace psv

#endif /* QUICKSORT_H */
