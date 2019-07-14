#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

namespace psv {

template <typename Func>
bool is_sorted(std::size_t size, Func f, int max = 1000) {
    std::vector<int> v;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, max);

    std::chrono::milliseconds sum{0};
    const int runs = 3;
    for (int run = 0; run < runs; ++run) {
        for (std::size_t i = 0; i < size; ++i) {
            v.emplace_back(dist(gen));
        }

        using clock = std::chrono::steady_clock;
        clock::time_point start = clock::now();

        f(v);

        clock::time_point end = clock::now();

        if (!std::is_sorted(v.begin(), v.end())) {
            return false;
        }

        sum +=
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }
    std::cout << "n = " << size << ' ' << (sum / runs).count() << "ms avg\n";
    return true;
}

}  // namespace psv

#endif /* UTILS_H */
