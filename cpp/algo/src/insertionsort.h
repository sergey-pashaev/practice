#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <vector>

namespace psv {

template <typename T>
void insertionsort(std::vector<T>& v) {
    if (v.empty()) return;

    const std::size_t size = v.size();
    for (std::size_t i = 1; i < size; ++i) {
        std::size_t j = i - 1;
        T key = v[i];
        while (j >= 0 && key < v[j]) {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = key;
    }
}

}  // namespace psv

#endif /* INSERTIONSORT_H */
