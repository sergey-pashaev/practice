// ex.1.11

// Расширяемые шаблоны: путем наследования или свойств?

#include <catch2/catch.hpp>

using namespace std;

// 2. Write template which checks if T has T* T::Clone() const memeber
// function.

struct WithClone {
    WithClone* Clone() { return 0; }
};

struct WithCloneConst {
    WithCloneConst* Clone() const { return 0; }
};

struct WithCloneDefault {
    WithCloneDefault* Clone(int = 42) const { return 0; }
};

struct WithoutClone {};

// 2a. T must have member function T* T::Clone() const
template <typename T>
class Ca {
   public:
    // SomeFunc won't be instantiated if SomeFunc is not used anywhere
    // type of return value is not checked
    void SomeFunc(const T* t) { t->Clone(); }
};

TEST_CASE("Ca without SomeFunc call") {
    Ca<WithClone> with;                 // fail: compiles, but no const
    Ca<WithCloneConst> with_const;      // ok
    Ca<WithCloneDefault> with_default;  // fail: shouldn't compile
    Ca<WithoutClone> without;           // fail: no clone

    // fix warnings
    (void)with;
    (void)with_const;
    (void)with_default;
    (void)without;
}

TEST_CASE("Ca with SomeFunc call") {
    WithClone with;
    WithCloneConst with_const;
    WithCloneDefault with_default;
    WithoutClone without;

    // fix warnings
    (void)with;
    (void)with_const;
    (void)with_default;
    (void)without;

    // Ca<WithClone>().SomeFunc(&with); // ok: fails to compile
    Ca<WithCloneConst>().SomeFunc(&with_const);      // ok
    Ca<WithCloneDefault>().SomeFunc(&with_default);  // fail: shouldn't compile
    // Ca<WithoutClone>().SomeFunc(&without);  // ok: fails to compile
}

// 2b. T must have member function T* T::Clone() const
template <typename T>
class Cb {
   public:
    // use dtor since class have only one dtor (but many ctors)
    ~Cb() {
        const T t;  // default ctor is required - not good
        // type of return value is not checked
        t.Clone();
    }
};

// 2c. T must have member function T* T::Clone() const
template <typename T>
class Cc {
   public:
    // use dtor since class have only one dtor (but many ctors)
    ~Cc() {
        // use pointer to function
        T* (T::*test)() const = &T::Clone;
        (void)test;  // fix unused variable warning
    }
};

// 2d. T must have member function T* T::Clone() const
template <typename T>
class Cd {
   private:
    bool ValidateRequirements() const {
        // use pointer to function
        T* (T::*test)() const = &T::Clone;
        (void)test;  // fix unused variable warning
        return true;
    }

   public:
    // use dtor since class have only one dtor (but many ctors)
    ~Cd() { assert(ValidateRequirements()); }
};

// 2e. T must have member function T* T::Clone() const
template <typename T>
class HasClone {
   public:
    static void Constraints() {
        // use pointer to function
        T* (T::*test)() const = &T::Clone;
        (void)test;  // fix unused variable warning
    }

    HasClone() {
        void (*p)() = Constraints;
        (void)p;  // fix unused variable warning
    }
};

template <typename T>
class Ce : HasClone<T> {};

TEST_CASE("HasClone") {
    // Ce<WithClone> with;  // ok: fails to compile
    Ce<WithCloneConst> with_const;  // ok
    // Ce<WithCloneDefault> with_default;  // ok: fails to compile
    // Ce<WithoutClone> without;  // ok: fails to compile

    // fix warnings
    // (void)with;
    (void)with_const;
    // (void)with_default;
    // (void)without;
}

// 3. Write template which checks if T is derived from Clonable(or other)

// 3a.
template <typename D, typename B>
class IsDerivedFrom1 {
   private:
    class No {};
    class Yes {
        No no[2];
    };  // needed to provide guarantee sizeof(No) != sizeof(Yes)

    static Yes Test(B*);  // return yes when parameter is convertible to B*
    static No Test(...);  // return no otherwise

   public:
    // enum is used because it should be calculated at compile time
    enum { Is = sizeof(Test(static_cast<D*>(0))) == sizeof(Yes) };  // do test
};

struct Clonable {};

template <typename T>
class X {
   private:
    bool ValidateRequirements() const {
        using Y = IsDerivedFrom1<T, Clonable>;
        assert(Y::Is);
        return true;
    }

   public:
    ~X() { assert(ValidateRequirements()); }
};

struct Derived : public Clonable {};
struct NotDerived {};

TEST_CASE("IsDerivedFrom1") {
    X<Derived> derived;         // ok
    // X<NotDerived> not_derived;  // ok: should not compile

    // fix warnings
    (void)derived;
    // (void)not_derived;
}

// 3b.
template <typename D, typename B>
class IsDerivedFrom2 {
   private:
    static void Constraints(D* p) {
        B* pb = p;
        (void)pb;  // fix warning
    }

   protected:
    IsDerivedFrom2() {
        void (*p)(D*) = Constraints;
        (void)p;  // fix warning;
    }
};

// TODO: fails to compile even if not used
// template <typename D>
// class IsDerivedFrom2<D, void> {
//    protected:
//     IsDerivedFrom2() {
//         char* p = (int*)0;  // compile error
//         (void)p;            // fix warning
//     }
// };

template <typename T>
class X2 : public IsDerivedFrom2<T, Clonable> {};

TEST_CASE("IsDerivedFrom2") {
    X2<Derived> derived;  // ok: compiles
    // X2<NotDerived> not_derived;  // ok: fails to compile

    // fix warnings
    (void)derived;
    // (void)not_derived;
}
