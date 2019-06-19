#include <catch.hpp>

#include <vector>

#include "utils.h"

#define xstr(a) str(a)
#define str(a) #a

#define SORTING_TEST(name)                              \
    TEST_CASE(xstr(name)) {                             \
        for (const std::size_t size : sizes) {          \
            REQUIRE(psv::is_sorted(size, test_##name)); \
        }                                               \
    }

static const std::vector<std::size_t> sizes = {0,   1,    2,    3,     100,
                                               500, 1000, 5000, 10000, 20000};

/// BUBBLE SORT
void bubblesort(std::vector<int>& v) {
    const int size = v.size();
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i; j < size; ++j) {
            if (v[i] > v[j]) std::swap(v[i], v[j]);
        }
    }
}

void test_bubblesort(std::vector<int>& v) { bubblesort(v); }

/// SELECTION SORT
void selectionsort(std::vector<int>& v) {
    const int size = v.size();
    for (int i = 0; i < size - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < size; ++j) {
            if (v[j] < v[min]) min = j;
        }
        v[i] = v[min];
    }
}

void test_selectionsort(std::vector<int>& v) { selectionsort(v); }

/// MERGE SORT
void merge(std::vector<int>& v, int lo, int mid, int hi) {
    int lsize = mid - lo + 1;
    int lbuf[lsize];
    int lidx = 0;
    for (int i = lo; i <= mid; ++i) lbuf[lidx++] = v[i];

    int rsize = hi - mid;
    int rbuf[rsize];
    int ridx = 0;
    for (int i = mid + 1; i <= hi; ++i) rbuf[ridx++] = v[i];

    ridx = lidx = 0;
    int k = lo;
    while (lsize && rsize) {
        if (lbuf[lidx] < rbuf[ridx]) {
            v[k++] = lbuf[lidx++];
            --lsize;
        } else {
            v[k++] = rbuf[ridx++];
            --rsize;
        }
    }

    while (lsize) {
        v[k++] = lbuf[lidx++];
        --lsize;
    }

    while (rsize) {
        v[k++] = rbuf[ridx++];
        --rsize;
    }
}

void mergesort(std::vector<int>& v, int lo, int hi) {
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
    int first_hi = lo;

    for (int i = lo; i < hi; ++i) {
        if (v[i] < v[pivot]) {
            std::swap(v[i], v[first_hi++]);
        }
    }

    std::swap(v[pivot], v[first_hi]);
    return first_hi;  // as new pivot;
}

void quicksort(std::vector<int>& v, int lo, int hi) {
    if (lo < hi) {
        int pivot = partition(v, lo, hi);
        quicksort(v, lo, pivot - 1);
        quicksort(v, pivot + 1, hi);
    }
}

void quicksort(std::vector<int>& v) { quicksort(v, 0, v.size() - 1); }

void test_quicksort(std::vector<int>& v) { quicksort(v); }

/// HEAP SORT
class Heap {
   public:
    explicit Heap(int size) : data_(size + 1), size_{0} {}

    void Insert(int v) {
        if (size_ > data_.size() - 1) throw std::out_of_range("heap is full");

        data_[++size_] = v;
        BubbleUp(size_);
    }

    int ExtractRoot() {
        if (size_ <= 0) throw std::out_of_range("heap is empty");

        int ret = data_[Root()];
        data_[Root()] = data_[--size_];
        data_.resize(data_.size() - 1);
        BubbleDown(Root());
        return ret;
    }

   private:
    //           0
    //           1
    //     2            3
    //  4    5       6     7
    // 8 9 10 11   12 13 14 15
    int Root() { return 1; }
    int Child(int n) { return n * 2; }
    int Parent(int n) {
        if (n == Root()) return 0;
        return n / 2;
    }

    void BubbleDown(int n) {
        int min = n;

        // iterate over children
        for (int i = 0; i < 2; ++i) {
            const int child = Child(n) + i;
            if (child < size_ && data_[child] < data_[min]) {
                min = child;
            }
        }

        if (min != n) {
            std::swap(data_[n], data_[min]);
            BubbleDown(min);
        }
    }

    void BubbleUp(int n) {
        if (n == Root()) return;

        const int parent = Parent(n);
        if (data_[parent] > data_[n]) {
            std::swap(data_[parent], data_[n]);
            BubbleUp(parent);
        }
    }

   private:
    std::vector<int> data_;
    int size_;
};

void heapsort(std::vector<int>& v) {
    Heap h(v.size());

    for (int i = 0; i < v.size(); ++i) {
        h.Insert(v[i]);
    }

    for (int i = 0; i < v.size(); ++i) {
        v[i] = h.ExtractRoot();
    }
}

void test_heapsort(std::vector<int>& v) { heapsort(v); }

// SORTING_TEST(bubblesort)
// SORTING_TEST(selectionsort)
SORTING_TEST(mergesort)
SORTING_TEST(quicksort)
SORTING_TEST(heapsort)

#if 0
/// BENCH
#include <random>
#include <vector>

static std::vector<int> make_random_vector(int size) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(1, 1000);

  std::vector<int> v;
  v.reserve(size);
  for (std::size_t i = 0; i < size; ++i) {
    v.emplace_back(dist(gen));
  }

  return v;
}

const int start = 1000;
const int end = 10000;

static void Mergesort(benchmark::State& state) {
    for (auto _ : state) {
        auto v = make_random_vector(state.range(0));
        mergesort(v);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(Mergesort)->Range(start, end);

static void Quicksort(benchmark::State& state) {
    for (auto _ : state) {
        auto v = make_random_vector(state.range(0));
        quicksort(v);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(Quicksort)->Range(start, end);

static void Heapsort(benchmark::State& state) {
    for (auto _ : state) {
        auto v = make_random_vector(state.range(0));
        heapsort(v);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(Heapsort)->Range(start, end);
#endif
