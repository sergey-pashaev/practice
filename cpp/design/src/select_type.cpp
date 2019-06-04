#include <catch2/catch.hpp>

#include <type_traits>
#include <vector>

// select type by bool flag
template <bool flag, class T, class U>
struct Select {
    using Result = T;
};

template <class T, class U>
struct Select<false, T, U> {
    using Result = U;
};

// make container which stores Ts by value or pointer depending on flag
template <class T, bool is_polymorphic>
struct Container {
    using ValueType = typename Select<is_polymorphic, T*, T>::Result;
    std::vector<ValueType> v;
};

template <class T>
using ValueContainer = Container<T, false>;

template <class T>
using PtrContainer = Container<T, true>;

struct Foo {};

TEST_CASE("select type") {
    ValueContainer<Foo> c1;
    REQUIRE(std::is_same<ValueContainer<Foo>::ValueType, Foo>::value);

    Container<Foo, true> c2;
    REQUIRE(std::is_same<PtrContainer<Foo>::ValueType, Foo*>::value);
}
