#include <catch2/catch.hpp>

#include <chapter-1/chapter.1.5.h>

namespace c_1_5 {

TEST_CASE("WidgetManager creates Widget only") {
    using MyWidgetManager = WidgetManager<OpNewCreator<Widget>>;
    MyWidgetManager m;
    REQUIRE(m.GetWidget().value == 42);
}

}  // namespace c_1_5

namespace c_1_5_1 {

TEST_CASE("WidgetManager creates Gadgets as well") {
    using MyWidgetManager = WidgetManager<OpNewCreator>;
    MyWidgetManager m;
    REQUIRE(m.GetWidget().value == 42);
    m.DoSomething();
}

}  // namespace c_1_5_1
