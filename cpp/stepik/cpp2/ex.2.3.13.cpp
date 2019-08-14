#include <algorithm>

int main() {
    auto gen_finder = [](int* b, int* e) {
        return [b, e](int n) {
            return std::find_if(b, e, [n](int x) { return x == n; }) != e;
        };
    };

    (void)gen_finder;
}
