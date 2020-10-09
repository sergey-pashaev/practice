#include <catch2/catch.hpp>

#include <memory>
#include <string>

namespace c_2_5 {

namespace {

template <typename T>
struct Type2Type {
    using OriginalType = T;
};

class Widget {
   public:
    Widget(int v, bool flag) {
        if (flag) {
            value_ = v;
        }
    }

   private:
    int value_;
};

// The point here is that we can "partially specialize" template functions
// through dummy template argument Type2Type.

template <class T, class U>
std::unique_ptr<T> Create(const U& arg, Type2Type<T>) {
    return std::make_unique<T>(arg);
}

template <class U>
std::unique_ptr<Widget> Create(const U& arg, Type2Type<Widget>) {
    return std::make_unique<Widget>(arg, true);
}

TEST_CASE("Type2Type") {
    auto string = Create("hello", Type2Type<std::string>());
    auto widget = Create(42, Type2Type<Widget>());
}

}  // namespace

}  // namespace c_2_5
