#include <catch2/catch.hpp>

#include <vector>

namespace c_2_10_1 {

class NullType {};

template <typename T>
class TypeTraits {
   private:
    template <class U>
    struct PointerTraits {
        enum { result = false };
        using PointeeType = NullType;
    };
    template <class U>
    struct PointerTraits<U*> {
        enum { result = true };
        using PointeeType = U;
    };

    template <class U> struct PToMTraits {
        enum { result = false };
    };
    template <class U, class V> struct PToMTraits<U V::*> {
        enum { result = true };
    };

   public:
    enum { is_pointer = PointerTraits<T>::result };
    using PointeeType = typename PointerTraits<T>::PointeeType;
    enum { is_member_pointer = PToMTraits<T>::result };
};

namespace {

struct Widget {
    int value;
};

TEST_CASE("PointerTraits") {
    REQUIRE(TypeTraits<int*>::is_pointer);
    REQUIRE(!TypeTraits<std::vector<int>::iterator>::is_pointer);

    REQUIRE(!TypeTraits<int*>::is_member_pointer);
    REQUIRE(TypeTraits<int Widget::*>::is_member_pointer);
}

}  // namespace

}  // namespace c_2_10_1
