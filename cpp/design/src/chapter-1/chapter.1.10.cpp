#include <catch2/catch.hpp>

#include <chapter-1/chapter.1.10.h>
#include <chapter-1/chapter.1.9.h>

namespace c_1_10 {

using Widget = c_1_9::Widget;

TEST_CASE("DefaultSmartPtrStorage") {
    using MyPtr = SmartPtr<Widget, NoChecking, NoSynchronization>;

    SECTION("Valid pointer to object") {
        MyPtr ptr(new Widget(5));
        REQUIRE(ptr->Value() == 5);
    }
}

}  // namespace c_1_10
