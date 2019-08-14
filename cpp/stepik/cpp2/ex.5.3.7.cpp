// Напишите метафункцию Fib<N>, которая вычисляет N-ое число Фибоначчи.
// Напоминаю, что последовательность Фибоначчи определяется следующим образом:
// Fib(0)=0
// Fib(1)=1
// Fib(N)=Fib(N−1)+Fib(N−2)

// Пример:﻿
// std::cout << Fib<10>::value;     // 55

#include <iostream>

template <int... Types>
struct IntList {};

template <int H, int... T>
struct IntList<H, T...> {
    static const int Head = H;
    using Tail = IntList<T...>;
};

template <>
struct IntList<> {};

int main() {
    using primes = IntList<2, 3, 5, 7, 11, 13>;

    constexpr int head = primes::Head;
    std::cout << head << '\n';

    using odd_primes = primes::Tail;
    std::cout << odd_primes::Head << '\n';
}
