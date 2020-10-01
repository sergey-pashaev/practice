#include <catch2/catch.hpp>

#include <utils/utils.h>

#include <chapter-1/chapter.1.5.h>
#include <chapter-1/chapter.1.9.h>

namespace c_1_9 {

using Widget = c_1_5::Widget;

TEST_CASE("NoChecking, NoSynchronization>") {
    using MyPtr = SmartPtr<Widget, NoChecking, NoSynchronization>;
    MyPtr ptr(new Widget(5));
    REQUIRE(ptr->value == 5);
}

TEST_CASE("EnforceNotNull, NoSynchronization") {
    using MyPtr = SmartPtr<Widget, EnforceNotNull, NoSynchronization>;
    MyPtr ptr(nullptr);
    REQUIRE_THROWS_AS(ptr->value, EnforceNotNull<Widget>::NullPointerException);
}

TEST_CASE("EnsureNotNull, NoSynchronization") {
    using MyPtr = SmartPtr<Widget, EnsureNotNull, NoSynchronization>;
    MyPtr ptr(nullptr);
    REQUIRE(ptr.operator->() == reinterpret_cast<Widget*>(42));
}

}  // namespace c_1_9
