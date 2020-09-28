#include <catch2/catch.hpp>

#include <utils/utils.h>

#include <chapter-1/chapter.1.8.h>

namespace c_1_8 {

TEST_CASE("Use SwitchPrototype with appropriate CreationPolicy") {
    using MyWidgetManager = WidgetManager<PrototypeCreator>;
    MyWidgetManager m;
    m.SwitchPrototype(new Widget(13));
    REQUIRE(m.GetWidget().value == 13);
}

#ifdef UNSUPPORTED_CREATION_POLICY_API
TEST_CASE("Use SwitchPrototype without appropriate CreationPolicy") {
    using MyWidgetManager = WidgetManager<OpNewCreator>;
    MyWidgetManager m;
    m.SwitchPrototype(new Widget(13));
    REQUIRE(m.GetWidget().value == 13);
}
#endif

TEST_CASE("Don't use SwitchPrototype without appropriate CreationPolicy") {
    using MyWidgetManager = WidgetManager<OpNewCreator>;
    MyWidgetManager m;
    REQUIRE(m.GetWidget().value == 42);
}

}  // namespace c_1_8
