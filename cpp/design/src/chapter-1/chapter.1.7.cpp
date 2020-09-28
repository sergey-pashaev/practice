#include <catch2/catch.hpp>

#include <utils/utils.h>

#include <chapter-1/chapter.1.5.h>
#include <chapter-1/chapter.1.7.h>

// Chapter 1.7
// You should protect your policy destructor.
namespace c_1_7 {

using Widget = c_1_5::Widget;

TEST_CASE("WidgetManager creator dtor access allowed") {
    using MyWidgetManager = c_1_5_1::WidgetManager<PrototypeCreator>;
    MyWidgetManager m;
    PrototypeCreator<Widget>* creator = &m;
    unused(creator);
    // Compiles, but we don't want it. Double free or corruption.
#ifdef PUBLIC_DTOR
    delete creator;
#endif
}

#ifdef PROTECTED_DTOR
TEST_CASE("WidgetManager creator dtor access forbidden") {
    using MyWidgetManager = c151::WidgetManager<OpNewCreator>;
    MyWidgetManager m;
    OpNewCreator<Widget>* creator = &m;
    // Compilation error:
    // calling a protected destructor of class 'OpNewCreator<Widget>'
    delete creator;
}
#endif

}  // namespace c_1_7
