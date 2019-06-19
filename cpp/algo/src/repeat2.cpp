#include <catch.hpp>

#include <iostream>
#include <vector>

#include "utils.h"

#define xstr(a) str(a)
#define str(a) #a

//        std::cout << xstr(name) << '\n';              \

#define SORTING_TEST(name)                              \
    TEST_CASE(xstr(name)) {                             \
        for (const std::size_t size : sizes) {          \
            REQUIRE(psv::is_sorted(size, test_##name)); \
        }                                               \
    }

static const std::vector<std::size_t> sizes = {
    0, 1, 2, 3, 100, 500, 1000, 5000, 10000, 50000, 100000};

/// BUBBLE SORT
void bubblesort(std::vector<int>& v) {
    const std::size_t size = v.size();
    if (size < 2) return;
    for (std::size_t i = 0; i < size - 1; ++i) {
        for (std::size_t j = i + 1; j < size; ++j) {
            if (v[i] > v[j]) std::swap(v[i], v[j]);
        }
    }
}

void test_bubblesort(std::vector<int>& v) { bubblesort(v); }

/// SELECTION SORT
void selectionsort(std::vector<int>& v) {
    const std::size_t size = v.size();
    if (size < 2) return;

    for (std::size_t i = 0; i < size - 1; ++i) {
        std::size_t min = i;
        for (std::size_t j = i + 1; j < size; ++j) {
            if (v[j] < v[min]) min = j;
        }

        if (min != i) std::swap(v[i], v[min]);
    }
}

void test_selectionsort(std::vector<int>& v) { selectionsort(v); }

/// MERGE SORT
// 0 1 2 3 4 5
void merge(std::vector<int>& v, int l, int m, int r) {
    int lsize = m - l + 1;
    int rsize = r - m;
    int lbuf[lsize];
    int rbuf[rsize];

    int li = 0;
    for (int i = l; i <= m; ++i) lbuf[li++] = v[i];

    int ri = 0;
    for (int i = m + 1; i <= r; ++i) rbuf[ri++] = v[i];

    li = ri = 0;
    int i = l;
    while (lsize && rsize) {
        if (lbuf[li] < rbuf[ri]) {
            v[i++] = lbuf[li++];
            --lsize;
        } else {
            v[i++] = rbuf[ri++];
            --rsize;
        }
    }

    while (lsize) {
        v[i++] = lbuf[li++];

        --lsize;
    }

    while (rsize) {
        v[i++] = rbuf[ri++];
        --rsize;
    }
}

void mergesort(std::vector<int>& v, int lo, int hi) {
    // if (v.size() < 2) return;
    if (hi > lo) {
        int mid = lo + (hi - lo) / 2;
        mergesort(v, lo, mid);
        mergesort(v, mid + 1, hi);
        merge(v, lo, mid, hi);
    }
}

void mergesort(std::vector<int>& v) { mergesort(v, 0, v.size() - 1); }

void test_mergesort(std::vector<int>& v) { mergesort(v); }

/// QUICK SORT
int partition(std::vector<int>& v, int lo, int hi) {
    int pivot = hi;
    int np = lo;

    for (int i = lo; i < pivot; ++i) {
        if (v[i] < v[pivot]) {
            std::swap(v[i], v[np++]);
        }
    }

    std::swap(v[pivot], v[np]);
    return np;
}

void quicksort(std::vector<int>& v, int lo, int hi) {
    if (hi > lo) {
        int p = partition(v, lo, hi);
        quicksort(v, lo, p - 1);
        quicksort(v, p + 1, hi);
    }
}

void quicksort(std::vector<int>& v) { quicksort(v, 0, v.size() - 1); }

void test_quicksort(std::vector<int>& v) { quicksort(v); }

/// HEAP SORT
class Heap {
   public:
    Heap(std::size_t size) : data_(size + 1), size_{0} {}
    void Insert(int v) {
        if (size_ > data_.size() - 1) throw std::out_of_range("full heap");

        data_[++size_] = v;
        BubbleUp(size_);
    }

    int ExtractRoot() {
        if (size_ <= 0) throw std::out_of_range("empty heap");

        int ret = data_[Root()];
        data_[Root()] = data_[size_ - 1];
        --size_;
        data_.resize(data_.size() - 1);
        BubbleDown(Root());
        return ret;
    }

   private:
    int Root() const { return 1; }
    int Child(int n) const { return n * 2; }
    int Parent(int n) const {
        if (n == Root()) return 0;
        return n / 2;
    }

    void BubbleUp(int n) {
        if (n <= Root()) return;

        const int parent = Parent(n);
        if (data_[n] < data_[parent]) {
            std::swap(data_[n], data_[parent]);
            BubbleUp(parent);
        }
    }

    void BubbleDown(int n) {
        const int child = Child(n);
        int min = n;
        for (int i = 0; i < 2; ++i) {
            if (child < size_ && data_[child + i] < data_[min]) {
                min = child + i;
            }
        }

        if (min != n) {
            std::swap(data_[min], data_[n]);
            BubbleDown(min);
        }
    }

   private:
    std::vector<int> data_;
    std::size_t size_;
};

void heapsort(std::vector<int>& v) {
    const std::size_t size = v.size();
    Heap h{v.size()};
    for (std::size_t i = 0; i < size; ++i) h.Insert(v[i]);
    for (std::size_t i = 0; i < size; ++i) v[i] = h.ExtractRoot();
}

void test_heapsort(std::vector<int>& v) { heapsort(v); }

// SORTING_TEST(bubblesort)
// SORTING_TEST(selectionsort)
// SORTING_TEST(mergesort)
SORTING_TEST(quicksort)
// SORTING_TEST(heapsort)
