#include <catch2/catch.hpp>

#include <memory>

namespace c_2_4 {

namespace {

template <int v>
struct Int2Type {
    enum { value = v };
};

struct Base {
    virtual ~Base() = default;
    virtual int Foo() const = 0;
    virtual Base* Clone() const = 0;
};

struct PolymorphicA : public Base {
    int Foo() const override { return 42; }
    PolymorphicA* Clone() const override { return new PolymorphicA(*this); }
};

struct PolymorphicB : public Base {
    int Foo() const override { return 7; }
    PolymorphicB* Clone() const override { return new PolymorphicB(*this); }
};

struct NonPolymorphic {
    int Foo() { return 1; }
};

// Point here is that we can do compile-time dispatching & select desired method
// to compile due to difference between types Int2Type<false> & Int2Type<true>.

#if RUNTIME_DISPATCH
template <typename T, bool is_polymorphic>
class NiftyContainer {
   public:
    int DoSomething(T* object) {
        T* new_object = nullptr;
        if (is_polymorphic) {
            new_object = object->Clone();
        } else {
            new_object = new T(*object);
        }
        int result = new_object->Foo();
        delete new_object;
        return result;
    }
};
#else
template <typename T, bool is_polymorphic>
class NiftyContainer {
   private:
    int DoSomething(T* object, Int2Type<true>) {
        T* new_object = object->Clone();
        int result = new_object->Foo();
        delete new_object;
        return result;
    }
    int DoSomething(T* object, Int2Type<false>) {
        T* new_object = new T(*object);
        int result = new_object->Foo();
        delete new_object;
        return result;
    }

   public:
    int DoSomething(T* object) {
        return DoSomething(object, Int2Type<is_polymorphic>());
    }
};
#endif

TEST_CASE("Int2Type") { REQUIRE(Int2Type<0>::value == 0); }

TEST_CASE("PolymorphicA") {
    NiftyContainer<PolymorphicA, true> nc;
    auto obj = std::make_unique<PolymorphicA>();
    REQUIRE(nc.DoSomething(obj.get()) == 42);
}

TEST_CASE("PolymorphicB") {
    auto obj = std::make_unique<PolymorphicB>();
    NiftyContainer<PolymorphicB, true> nc;
    REQUIRE(nc.DoSomething(obj.get()) == 7);
}

TEST_CASE("NonPolymorphic") {
    auto obj = std::make_unique<NonPolymorphic>();
    NiftyContainer<NonPolymorphic, false> nc;
    REQUIRE(nc.DoSomething(obj.get()) == 1);
}

}  // namespace

}  // namespace c_2_4
