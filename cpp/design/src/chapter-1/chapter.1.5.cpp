#include <catch2/catch.hpp>

#include <chapter-1/chapter.1.5.h>

namespace c_1_5 {

TEST_CASE("c.1.5.WidgetManager") {
    using MyWidgetManager = WidgetManager<OpNewCreator<Widget>>;
    MyWidgetManager m;
}

}  // namespace c_1_5

namespace c_1_5_1 {

TEST_CASE("c.1.5.1.WidgetManager") {
    using MyWidgetManager = WidgetManager<OpNewCreator>;
    MyWidgetManager m;
    m.DoSomething();
}

}  // namespace c_1_5_1
