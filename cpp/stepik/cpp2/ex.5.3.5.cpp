// Напишите метафункцию Fib<N>, которая вычисляет N-ое число Фибоначчи.
// Напоминаю, что последовательность Фибоначчи определяется следующим образом:
// Fib(0)=0
// Fib(1)=1
// Fib(N)=Fib(N−1)+Fib(N−2)

// Пример:﻿
// std::cout << Fib<10>::value;     // 55

#include <iostream>

template <int N>
struct Fib {
    static const int value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template <>
struct Fib<0> {
    static const int value = 0;
};

template <>
struct Fib<1> {
    static const int value = 1;
};

int main() { std::cout << Fib<10>::value << '\n'; }
