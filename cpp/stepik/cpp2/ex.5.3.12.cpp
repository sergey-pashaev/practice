// typelist
template <typename... Types>
struct TypeList {};

template <typename H, typename... T>
struct TypeList<H, T...> {
    using Head = H;
    using Tail = TypeList<T...>;
};

template <>
struct TypeList<> {};

// int list
template <int... Types>
struct IntList {};

template <int H, int... T>
struct IntList<H, T...> {
    static const int Head = H;
    using Tail = IntList<T...>;
};

template <>
struct IntList<> {};

// length
template <typename T>
struct Length {
    static const int value = 1 + Length<typename T::Tail>::value;
};

template <>
struct Length<IntList<>> {
    static const int value = 0;
};

// int cons
template <int H, typename T>
struct IntCons {};

template <int H, int... Ints>
struct IntCons<H, IntList<Ints...>> {
    using type = IntList<H, Ints...>;
};

template <int H>
struct IntCons<H, IntList<>> {
    using type = IntList<H>;
};

// generate
template <int N, int V = 0>
struct Generate {
    using type =
        typename IntCons<V, typename Generate<N - 1, V + 1>::type>::type;
};

template <int V>
struct Generate<1, V> {
    using type = IntList<V>;
};

template <int V>
struct Generate<0, V> {
    using type = IntList<>;
};

// Напишите две метафункции для работы c IntList:

// IntCons позволяет увеличить список на один элемент — он добавляется в начало
// списка.
// Generate позволяет сгенерировать список длины N с числами от 0 до N - 1.
// Пример:
// using L1 = IntList<2,3,4>;

// using L2 = IntCons<1, L1>::type;   // IntList<1,2,3,4>

// using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>

// Hint: у метафункции Generate удобно сделать второй параметр со значением по
// умолчанию.

// main
#include <iostream>

template <typename T>
void check() {
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

int main() {
    // using L1 = IntList<2, 3, 4>;
    // check<L1>();
    // using L2 = IntCons<1, L1>::type;
    // check<L2>();
    // using L3 = IntCons<0, L2>::type;
    // check<L3>();
    using G0 = Generate<0>::type;
    check<G0>();
    using G1 = Generate<1>::type;
    check<G1>();
    using G2 = Generate<2>::type;
    check<G2>();
    using G3 = Generate<3>::type;
    check<G3>();
    using G5 = Generate<5>::type;
    check<G5>();
}
