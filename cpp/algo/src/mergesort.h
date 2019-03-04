#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

#include <iostream>

namespace psv {

template <typename T>
void merge(std::vector<T>& v, int lo, int mid, int hi) {
    // copy [lo, mid] to buf
    int lsize = mid - lo + 1;
    T lbuf[lsize];
    int l = 0;
    for (int i = lo; i <= mid; ++i) lbuf[l++] = v[i];

    // copy (mid, hi] to buf
    int rsize = hi - mid;
    T rbuf[rsize];
    int r = 0;
    for (int i = mid + 1; i <= hi; ++i) rbuf[r++] = v[i];

    // compare & merge while both not empty
    int i = lo;
    l = r = 0;
    while (lsize && rsize) {
        if (lbuf[l] < rbuf[r]) {
            v[i++] = lbuf[l++];
            --lsize;
        } else {
            v[i++] = rbuf[r++];
            --rsize;
        }
    }

    // add leftovers

    while (lsize > 0) {
        v[i++] = lbuf[l++];
        --lsize;
    }

    while (rsize > 0) {
        v[i++] = rbuf[r++];
        --rsize;
    }
}

template <typename T>
void mergesort(std::vector<T>& v, int lo, int hi) {
    if (lo < hi) {
        int mid = (hi - lo) / 2 + lo;  // avoid overflow
        mergesort(v, lo, mid);
        mergesort(v, mid + 1, hi);
        merge(v, lo, mid, hi);
    }
}

template <typename T>
void mergesort(std::vector<T>& v) {
    mergesort(v, 0, v.size() - 1);
}

}  // namespace psv

#endif /* MERGESORT_H */
