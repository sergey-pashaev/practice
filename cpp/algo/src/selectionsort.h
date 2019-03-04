#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include <vector>

namespace psv {

template <typename T>
void selectionsort(std::vector<T>& v) {
    if (v.empty()) return;

    const std::size_t size = v.size();
    for (std::size_t i = 0; i < size - 1; ++i) {
        std::size_t min = i;
        for (std::size_t j = i; j < size; ++j) {
            if (v[j] < v[min]) {
                min = j;
            }
        }

        if (min != i) {
            std::swap(v[i], v[min]);
        }
    }
}

}  // namespace psv

#endif /* SELECTIONSORT_H */
