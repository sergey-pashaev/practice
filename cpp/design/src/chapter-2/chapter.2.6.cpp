#include <catch2/catch.hpp>

#include <type_traits>
#include <vector>

namespace c_2_6 {

namespace {

template <bool flag, class T, class U>
struct Select {
    using Result = T;
};

template <class T, class U>
struct Select<false, T, U> {
    using Result = U;
};

template <class T, bool is_polymorphic>
class NiftyContainer {
   public:
    using ValueType = typename Select<is_polymorphic, T*, T>::Result;

   private:
    std::vector<ValueType> values_;
};

template <class T>
using ValueContainer = NiftyContainer<T, false>;

template <class T>
using PtrContainer = NiftyContainer<T, true>;

struct Widget {};

TEST_CASE("Select") {
    ValueContainer<Widget> c1;
    REQUIRE(std::is_same<ValueContainer<Widget>::ValueType, Widget>::value);

    PtrContainer<Widget> c2;
    REQUIRE(std::is_same<PtrContainer<Widget>::ValueType, Widget*>::value);
}

}  // namespace

}  // namespace c_2_6
