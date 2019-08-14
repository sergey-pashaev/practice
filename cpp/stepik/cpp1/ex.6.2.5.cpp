#include <cstddef>

template <typename T, typename U>
void copy_n(T* to, const U* from, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        to[i] = T(from[i]);
    }
}

int main() {}
