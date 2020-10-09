#include <catch2/catch.hpp>

#include <vector>

namespace c_2_7 {

namespace {

// T -> U
template <class T, class U>
class Conversion {
   private:
    // sizof(Big) > sizeof(Small)
    using Small = char;
    class Big {
        Small dummy[2];
    };

    // If it possible for compiler to convert return type of MakeT (T) to U -
    // Small Test(const U&) override should be selected, Big Test(...) -
    // otherwise.
    static T MakeT();
    static Small Test(const U&);
    static Big Test(...);

   public:
    enum { exists = sizeof(Test(MakeT())) == sizeof(Small), sametype = false };
};

template <class T>
class Conversion<T, T> {
   public:
    enum { exists = true, sametype = true };
};

class Base {};
class Derived : public Base {};
class Separate {};

// T - > U
#define SUPERSUBCLASS(T, U)                    \
    (Conversion<const U*, const T*>::exists && \
     !Conversion<const T*, const void*>::sametype)

TEST_CASE("Conversion") {
    REQUIRE(Conversion<double, int>::exists);
    REQUIRE(!Conversion<char, char*>::exists);
    REQUIRE(!Conversion<size_t, std::vector<int>>::exists);
    REQUIRE(SUPERSUBCLASS(Base, Base));
    REQUIRE(SUPERSUBCLASS(Base, Derived));
    REQUIRE(!SUPERSUBCLASS(Derived, Base));
    REQUIRE(!SUPERSUBCLASS(Base, Separate));
}

}  // namespace

}  // namespace c_2_7
