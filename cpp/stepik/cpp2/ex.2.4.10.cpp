#include <utility>  // для std::move и std::forward

// реализация функции apply
template <typename Func, typename... Args>
auto apply(Func f, Args&&... args) -> decltype(f(std::forward<Args>(args)...)) {
    return f(std::forward<Args>(args)...);
}

int main() {}
