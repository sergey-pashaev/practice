#include <catch2/catch.hpp>

#include <iostream>
#include <memory>

class Interface {
   public:
    virtual ~Interface() {}
    virtual int Function() = 0;
};

template <class T, class P>
std::unique_ptr<Interface> MakeAdapter(const T& obj, const P& arg) {
    class Local : public Interface {
       public:
        Local(const T& obj, const P& arg) : obj_{obj}, arg_{arg} {}
        int Function() override { return obj_(arg_); }

       private:
        T obj_;
        P arg_;
    };

    return std::make_unique<Local>(obj, arg);
}

struct Foo {
    int operator()(int v) { return v; }
};

TEST_CASE("interface adapter") {
    Foo foo;
    auto adapter = MakeAdapter(foo, 5);
    REQUIRE(adapter->Function() == 5);
}