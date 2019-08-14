#include <cstddef>

template <class It>
size_t max_increasing_len(It p, It q) {
    size_t max = 1;
    size_t len = 1;
    It prev = p;
    for (It prev = p; p != q; prev = p++) {
        if (*p > *prev) {
            len++;
            if (len > max) max = len;
        } else {
            len = 1;
        }
    }

    return max;
}

int main() {}
