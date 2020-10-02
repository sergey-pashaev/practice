#include <catch2/catch.hpp>

#include <utils/utils.h>

#include <chapter-1/chapter.1.5.h>
#include <chapter-1/chapter.1.9.h>

namespace c_1_9 {

class Widget {
   public:
    Widget() = default;
    explicit Widget(int v) : value_{v} {}
    void Increment() { ++value_; }
    int Value() const { return value_; }

   private:
    int value_ = 0;
};

TEST_CASE("NoChecking") {
    using MyPtr = SmartPtr<Widget, NoChecking, NoSynchronization>;

    SECTION("Valid pointer to object") {
        MyPtr ptr(new Widget(5));
        REQUIRE(ptr->Value() == 5);
    }

#ifdef NO_CHECKING_NULLPTR
    SECTION("Null pointer") {
        MyPtr ptr(nullptr);
        REQUIRE(ptr->Value() == 0);
    }
#endif
}

TEST_CASE("EnforceNotNull") {
    using MyPtr = SmartPtr<Widget, EnforceNotNull, NoSynchronization>;

    SECTION("Valid pointer to object") {
        MyPtr ptr(new Widget(5));
        REQUIRE(ptr->Value() == 5);
    }

    SECTION("Null pointer") {
        MyPtr ptr(nullptr);
        REQUIRE_THROWS_AS(ptr->Value(),
                          EnforceNotNull<Widget>::NullPointerException);
    }
}

TEST_CASE("EnsureNotNull") {
    using MyPtr = SmartPtr<Widget, EnsureNotNull, NoSynchronization>;

    SECTION("Valid pointer to object") {
        MyPtr ptr(new Widget(5));
        REQUIRE(ptr->Value() == 5);
    }

    SECTION("Null pointer") {
        MyPtr ptr(nullptr);
        REQUIRE(ptr->Value() == 0);
    }
}

}  // namespace c_1_9
