#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <vector>

namespace psv {

template <typename T>
void bubblesort(std::vector<T>& v) {
    if (v.empty()) return;

    const std::size_t size = v.size();
    for (std::size_t i = 0; i < size - 1; ++i) {
        for (std::size_t j = i; j < size; ++j) {
            if (v[i] > v[j]) std::swap(v[i], v[j]);
        }
    }
}

}  // namespace psv

#endif /* BUBBLESORT_H */
