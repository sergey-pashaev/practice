/*
В данной задаче от вас потребуется реализовать аналоги популярной
концепции MapReduce в терминах потоков.

Напишите функцию map_reduce, которая принимает на вход:

- итератор на начало последовательности,
- итератор на конец последовательности,
- унарный функтор, который можно применить к элементам последовательности,
- бинарный функтор, который можно применить к результатам применения первого
функтора,
- количество потоков.

Результат вызова map_reduce
auto res = map_reduce(p, q, f1, f2, num);

должен быть эквивалентен результату следующего кода:
auto res = f1(*p);
while(++p != q)
    res = f2(res, f1(*p));

только выполнение этого кода должно быть разбито на num потоков. Для
этого можно разбить диапазон [p,q) на num частей, выполнить вычисление
для каждой части в отдельном потоке и объединить результаты из всех
потоков.

Пример:

std::list<int> l = {1,2,3,4,5,6,7,8,9,10};
// параллельное суммирование в 3 потока
auto sum = map_reduce(l.begin(), l.end(),
             [](int i){return i;},
                      std::plus<int>(), 3);

// проверка наличия чётных чисел в четыре потока
auto has_even = map_reduce(l.begin(), l.end(),
                 [](int i){return i % 2 == 0;},
                std::logical_or<bool>(), 4);
Гарантии:

Длина последовательности не меньше количества потоков.
Функция f2 ассоциативна.

Требования:

- Реализовать map_reduce нужно с использование std::async.
- Функция не должна изменять или копировать последовательность.

- У потоков не должно быть разделяемых неконстантных данных
  (соответственно, не нужны примитивы синхронизации).
*/

// заголовок <future> уже подключён.
// заново подключать не нужно

// // реализация функции mapreduce
// ... map_reduce(... p, ... q, ... f1, ... f2,  size_t threads)
// {

// }

#include <algorithm>
#include <functional>
#include <future>
#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

using namespace std;

template <typename Iterator>
void print_ranges(const std::vector<std::pair<Iterator, Iterator>>& ranges) {
    cout << "ranges:\n";
    for (const auto& e : ranges) {
        auto beg = e.first;
        auto end = e.second;

        cout << *beg << ' ';
        while (++beg != end) {
            cout << *beg << ' ';
        }
        cout << '\n';
    }
}

template <typename Iterator>
std::vector<std::pair<Iterator, Iterator>> divide_work(Iterator beg,
                                                       Iterator end,
                                                       std::size_t n) {
    std::vector<std::pair<Iterator, Iterator>> ranges;
    if (n == 0) return ranges;

    ranges.reserve(n);

    auto dist = std::distance(beg, end);
    n = std::min<size_t>(n, dist);
    auto chunk = dist / n;
    auto remainder = dist % n;

    for (std::size_t i = 0; i < n - 1; ++i) {
        auto next_end = std::next(beg, chunk + (remainder ? 1 : 0));
        ranges.emplace_back(beg, next_end);
        beg = next_end;
        if (remainder) remainder -= 1;
    }

    ranges.emplace_back(beg, end);
    return ranges;
}

template <typename Iterator, typename F1, typename F2>
auto worker(Iterator p, Iterator q, F1 f1, F2 f2)
    -> decltype(f2(f1(*p), f1(*p))) {
    decltype(f2(f1(*p), f1(*p))) res = f1(*p);
    while (++p != q) {
        res = f2(res, f1(*p));
    }

    return res;
}

template <typename Iterator, typename F1, typename F2>
auto map_reduce(Iterator p, Iterator q, F1 f1, F2 f2, size_t threads)
    -> decltype(f2(f1(*p), f1(*p))) {
    auto ranges = divide_work(p, q, threads);

    typedef decltype(f2(f1(*p), f1(*p))) f2_result;
    std::vector<std::future<f2_result>> futures;
    futures.reserve(ranges.size());

    for (const auto& range : ranges) {
        futures.emplace_back(std::async(std::launch::async, [&] {
            return worker(range.first, range.second, f1, f2);
        }));
    }

    auto beg = futures.begin();
    auto end = futures.end();
    auto res = (*beg).get();
    while (++beg != end) {
        res = f2(res, (*beg).get());
    }

    return res;
}

int main() {
    {
        std::list<std::string> s = {"abc", "def", "ghl"};
        auto sum = map_reduce(s.begin(), s.end(),
                              [](const string& s) { return s.size(); },
                              std::plus<size_t>(), 2);
        cout << "sum: " << sum << '\n';
    }

    std::list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // параллельное суммирование в 3 потока
    auto sum = map_reduce(l.begin(), l.end(), [](int i) { return i; },
                          std::plus<int>(), 3);
    cout << "sum: " << sum << '\n';

    // проверка наличия чётных чисел в четыре потока
    auto has_even =
        map_reduce(l.begin(), l.end(), [](int i) { return i % 2 == 0; },
                   std::logical_or<bool>(), 4);
    cout << "has_even: " << has_even << '\n';
}
