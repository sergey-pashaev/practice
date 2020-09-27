#include <catch2/catch.hpp>

#include <memory>

#include "creator.h"

TEST_CASE("OpNewCreator") {
    OpNewCreator<int> creator;
    std::unique_ptr<int> ip(creator.Create());
    REQUIRE(ip);
}

TEST_CASE("MallocCreator") {
    MallocCreator<int> creator;
    std::unique_ptr<int> ip(creator.Create());
    REQUIRE(ip);
}

struct Widget {
    Widget(int v = 42) : value{v} {}
    Widget* Clone() const { return new Widget(value); }

    int value;
};

TEST_CASE("PrototypeCreator") {
    SECTION("empty") {
        PrototypeCreator<Widget> creator;
        REQUIRE(creator.Create() == nullptr);
        REQUIRE(creator.GetPrototype() == nullptr);
    }

    SECTION("valid") {
        Widget prototype{42};
        PrototypeCreator<Widget> creator(&prototype);
        std::unique_ptr<Widget> ip(creator.Create());
        REQUIRE(ip);
        REQUIRE(ip->value == prototype.value);

        creator.SetPrototype(nullptr);
        REQUIRE(creator.Create() == nullptr);
    }
}

// Chapter 1.5
// Usage of creator class as template argument
namespace c15 {

template <class CreationPolicy>
class WidgetManager : public CreationPolicy {
   public:
    WidgetManager() : widget_{this->Create()} {}

   private:
    std::unique_ptr<Widget> widget_;
};

TEST_CASE("c.1.5.WidgetManager") {
    using MyWidgetManager = WidgetManager<OpNewCreator<Widget>>;
    MyWidgetManager m;
}

}  // namespace c15

// Chapter 1.5.1
// In 1.5 WidgetManager can use CreationPolicy only for type Widget. It would be
// great if we can create not only Widgets with this CreationPolicy.
namespace c151 {

struct Gadget {};

template <template <class Created> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget> {
   public:
    WidgetManager() : widget_{this->Create()} {}
    void DoSomething() {
        // Now we cant create gadgets also.
        std::unique_ptr<Gadget> g{CreationPolicy<Gadget>().Create()};
    }

   private:
    std::unique_ptr<Widget> widget_;
};

TEST_CASE("c.1.5.1.WidgetManager") {
    using MyWidgetManager = WidgetManager<OpNewCreator>;
    MyWidgetManager m;
    m.DoSomething();
}
}  // namespace c151

// Chapter 1.7
// You should protect your policy destructor.
namespace c17 {

TEST_CASE("c.1.7.WidgetManager creator dtor access allowed") {
    using MyWidgetManager = c151::WidgetManager<PrototypeCreator>;
    MyWidgetManager m;
    PrototypeCreator<Widget>* creator = &m;
    // Compiles, but we don't want it. Double free or corruption.
#ifdef C17_PUBLIC_DTOR
    delete creator;
#endif
}

template <class T>
struct OpNewCreator {
    static T* Create() { return new T; }

   protected:
    // Allow destructor for derived classes only.
    ~OpNewCreator() = default;
};

#ifdef C17_PROTECTED_DTOR
TEST_CASE("c.1.7.WidgetManager creator dtor access forbidden") {
    using MyWidgetManager = c151::WidgetManager<OpNewCreator>;
    MyWidgetManager m;
    OpNewCreator<Widget>* creator = &m;
    // Compilation error:
    // calling a protected destructor of class 'OpNewCreator<Widget>'
    delete creator;
}
#endif

}  // namespace c17
