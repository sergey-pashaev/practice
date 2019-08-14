#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

using namespace std;

// алгоритм должен работать с forward итераторами
// и возвращать итератор, который потом будет передан
// в метод erase соответствующего контейнера
template <class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n) {
    for (; p != q && n; --n, ++p)
        ;
    if (p != q) {
        for (FwdIt last = p; ++last != q; *p++ = *last)
            ;
    }
    return p;
}

int main(int argc, char *argv[]) {
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for_each(v.begin(), v.end(), [](int x) { cout << x << ' '; });
    cout << '\n';

    // remove_nth(v.begin(), v.end(), 5);
    v.erase(remove_nth(v.begin(), v.end(), std::atoi(argv[1])), v.end());

    for_each(v.begin(), v.end(), [](int x) { cout << x << ' '; });
    cout << '\n';
}
