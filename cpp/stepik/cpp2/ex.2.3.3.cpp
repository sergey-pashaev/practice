#include <tuple>

template <int n1, int n2, typename Tuple>
auto to_pair(const Tuple& tuple)
    -> decltype(std::make_pair(std::get<n1>(tuple), std::get<n2>(tuple))) {
    return std::make_pair(std::get<n1>(tuple), std::get<n2>(tuple));
}

int main() {}
