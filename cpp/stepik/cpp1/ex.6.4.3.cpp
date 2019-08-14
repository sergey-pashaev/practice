#include <cstddef>  // size_t

template <typename T, int N>
size_t array_size(T (&t)[N]) {
    return N;
}

int main() {}
