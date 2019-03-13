#include <catch.hpp>

#include <vector>

template <typename T>
int binary_search_iterative(std::vector<T>& v, int lo, int hi, T x) {
    int mid;
    while (hi >= lo) {
        mid = lo + (hi - lo) / 2;
        if (x < v[mid]) {
            hi = mid - 1;
        } else if (x > v[mid]) {
            lo = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

template <typename T>
int binary_search_recursive(std::vector<T>& v, int lo, int hi, T x) {
    while (hi >= lo) {
        int mid = lo + (hi - lo) / 2;
        if (x < v[mid]) {
            return binary_search_recursive(v, lo, mid - 1, x);
        } else if (x > v[mid]) {
            return binary_search_recursive(v, mid + 1, hi, x);
        } else {
            return mid;
        }
    }

    return -1;
}

template <typename T>
int binary_search(std::vector<T>& v, T x) {
    return binary_search_iterative(v, 0, v.size() - 1, x);
}

TEST_CASE("binary search") {
    std::size_t sizes[] = {0, 1, 2, 3, 100};

    for (std::size_t i = 0; i < (sizeof(sizes) / sizeof(sizes[0])); ++i) {
        std::vector<int> v;
        const int size = sizes[i];
        v.reserve(size);
        for (int i = 0; i < size; ++i) {
            v.push_back(i);
        }

        if (size) {
            for (int i = 0; i < size; ++i) {
                REQUIRE(binary_search(v, i) == i);
            }

            REQUIRE(binary_search( v, size) == -1);
        } else {
            REQUIRE(binary_search(v, 1) == -1);
        }
    }
}
