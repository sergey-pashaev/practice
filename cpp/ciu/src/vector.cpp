#include <catch.hpp>

#include <psv/vector.h>

using psv::Vector;

TEST_CASE("vector construction", "[vector][template]") {
    typedef int T;
    T val0 = 1;
    T val1 = 2;

    // default ctor
    Vector<T> v1;
    REQUIRE(v1.Size() == 0);
    REQUIRE(v1.Capacity() > 0);
    REQUIRE(v1.IsEmpty());

    // capacity ctor
    const int cap = 32;
    Vector<T> v2(cap);
    v2.PushBack(val0);
    v2.PushBack(val1);
    REQUIRE(v2.Size() == 2);
    REQUIRE(v2.Capacity() == cap);
    REQUIRE(!v2.IsEmpty());

    // copy ctor
    Vector<T> v3(v2);
    REQUIRE(v3.Size() == 2);
    REQUIRE(v3.Capacity() == cap);
    REQUIRE(!v3.IsEmpty());
    REQUIRE(v3.At(0) == val0);
    REQUIRE(v3.At(1) == val1);

    // move ctor
    Vector<T> v4(std::move(v3));
    REQUIRE(v4.Size() == 2);
    REQUIRE(v4.Capacity() == cap);
    REQUIRE(!v4.IsEmpty());
    REQUIRE(v4.At(0) == val0);
    REQUIRE(v4.At(1) == val1);

    // v3 now with empty capacity
    REQUIRE(v3.Size() == 0);
    REQUIRE(v3.Capacity() == 0);
    REQUIRE(v3.IsEmpty());

    // assignment op
    Vector<T> v5 = v2;
    REQUIRE(v5.Size() == 2);
    REQUIRE(v5.Capacity() == cap);
    REQUIRE(!v5.IsEmpty());
    REQUIRE(v5.At(0) == val0);
    REQUIRE(v5.At(1) == val1);
}

TEST_CASE("vector insert", "[vector][template]") {
    typedef int T;

    Vector<T> v1;
    v1.PushBack(0);
    v1.PushBack(1);

    // insert before first element
    REQUIRE_THROWS_AS(v1.Insert(-1, 2), std::out_of_range);
    REQUIRE(v1.Size() == 2);

    // insert out of range
    REQUIRE_THROWS_AS(v1.Insert(v1.Size() + 1, 2), std::out_of_range);
    REQUIRE(v1.Size() == 2);

    // insert after last element
    REQUIRE_NOTHROW(v1.Insert(v1.Size(), 2));
    REQUIRE(v1.Size() == 3);

    REQUIRE(v1.At(0) == 0);
    REQUIRE(v1.At(1) == 1);
    REQUIRE(v1.At(2) == 2);

    // insert in the middle
    REQUIRE_NOTHROW(v1.Insert(1, 3));
    REQUIRE(v1.Size() == 4);
    REQUIRE(v1.At(0) == 0);
    REQUIRE(v1.At(1) == 3);
    REQUIRE(v1.At(2) == 1);
    REQUIRE(v1.At(3) == 2);

    // insert in the beginning
    REQUIRE_NOTHROW(v1.Insert(0, 4));
    REQUIRE(v1.Size() == 5);
    REQUIRE(v1.At(0) == 4);
    REQUIRE(v1.At(1) == 0);
    REQUIRE(v1.At(2) == 3);
    REQUIRE(v1.At(3) == 1);
    REQUIRE(v1.At(4) == 2);
}

TEST_CASE("vector delete", "[vector][template]") {
    typedef int T;

    Vector<T> v1;
    v1.PushBack(0);
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    v1.PushBack(4);

    // delete before first element
    REQUIRE_THROWS_AS(v1.Delete(-1), std::out_of_range);

    // delete out of range
    REQUIRE_THROWS_AS(v1.Delete(v1.Size()), std::out_of_range);

    // delete last element
    REQUIRE_NOTHROW(v1.Delete(v1.Size() - 1));
    REQUIRE(v1.Size() == 4);
    REQUIRE(v1.At(0) == 0);
    REQUIRE(v1.At(1) == 1);
    REQUIRE(v1.At(2) == 2);
    REQUIRE(v1.At(3) == 3);

    // delete in the middle
    REQUIRE_NOTHROW(v1.Delete(1));
    REQUIRE(v1.Size() == 3);
    REQUIRE(v1.At(0) == 0);
    REQUIRE(v1.At(1) == 2);
    REQUIRE(v1.At(2) == 3);

    // delete in the beginning
    REQUIRE_NOTHROW(v1.Delete(0));
    REQUIRE(v1.Size() == 2);
    REQUIRE(v1.At(0) == 2);
    REQUIRE(v1.At(1) == 3);
}

TEST_CASE("vector auto increase", "[vector][template]") {
    typedef int T;

    const int cap = 16;
    Vector<T> v1(cap);
    REQUIRE(v1.Capacity() == cap);

    for (int i = 0; i < cap; ++i) v1.PushBack(i);
    REQUIRE(v1.Size() == cap);
    REQUIRE(v1.Capacity() == cap);

    v1.PushBack(cap);
    REQUIRE(v1.Size() == cap + 1);
    REQUIRE(v1.Capacity() == cap * 2);
}

TEST_CASE("vector reserve", "[vector][template]") {
    typedef int T;

    const int cap = 16;
    Vector<T> v1(cap);
    REQUIRE(v1.Capacity() == cap);

    // reserve one more
    REQUIRE_NOTHROW(v1.Reserve(cap + 1));
    REQUIRE(v1.Capacity() == cap + 1);

    // reserve less than we have currently
    REQUIRE_NOTHROW(v1.Reserve(cap / 2));
    REQUIRE(v1.Capacity() == cap + 1);
}

TEST_CASE("vector push & pop", "[vector][template]") {
    typedef int T;

    Vector<T> v1;

    // pop empty vector
    REQUIRE_THROWS_AS(v1.PopBack(), std::out_of_range);

    v1.PushBack(0);
    v1.PushBack(1);
    REQUIRE(v1.Size() == 2);
    REQUIRE(v1.At(0) == 0);
    REQUIRE(v1.At(1) == 1);

    REQUIRE_NOTHROW(v1.PopBack() == 1);
    REQUIRE(v1.Size() == 1);
    REQUIRE(v1.At(0) == 0);

    REQUIRE_NOTHROW(v1.PopBack() == 0);
    REQUIRE(v1.Size() == 0);
}

TEST_CASE("vector find", "[vector][template]") {
    typedef int T;

    const int n = 64;
    Vector<T> v1;
    for (int i = 0; i < n; ++i) v1.PushBack(i);

    REQUIRE(v1.Find(0) == 0);
    REQUIRE(v1.Find(n - 1) == n - 1);

    v1.At(0) = 1;

    REQUIRE(v1.Find(0) == -1);
    REQUIRE(v1.Find(n) == -1);
}

TEST_CASE("vector remove", "[vector][template]") {
    typedef int T;

    Vector<T> v1;
    v1.PushBack(0);
    v1.PushBack(1);
    v1.PushBack(3);
    v1.PushBack(2);
    v1.PushBack(3);
    v1.PushBack(3);
    v1.PushBack(4);
    v1.PushBack(3);

    REQUIRE(v1.Size() == 8);

    // remove non-existing element
    REQUIRE(v1.Remove(-1) == 0);
    REQUIRE(v1.Size() == 8);

    // remove 3
    REQUIRE(v1.Remove(3) == 4);
    REQUIRE(v1.Size() == 4);

    REQUIRE(v1.At(0) == 0);
    REQUIRE(v1.At(1) == 1);
    REQUIRE(v1.At(2) == 2);
    REQUIRE(v1.At(3) == 4);
}
