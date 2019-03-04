#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <random>
#include <vector>

namespace psv {

template <typename Func>
bool is_sorted(std::size_t size, Func f) {
    std::vector<int> v;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    for (std::size_t i = 0; i < size; ++i) {
        v.emplace_back(dist(gen));
    }

    f(v);

    return std::is_sorted(v.begin(), v.end());
}

}  // namespace psv

#endif /* UTILS_H */
