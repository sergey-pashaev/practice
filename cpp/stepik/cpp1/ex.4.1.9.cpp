#include <iostream>

struct Foo {
    void say() const { std::cout << "Foo says: " << msg << "\n"; }

   protected:
    Foo(const char *msg) : msg(msg) {}

   private:
    const char *msg;
};

void foo_says(const Foo &foo) { foo.say(); }

// Вам нужно определить функцию get_foo, как описано в задании,
// чтобы компилировался и работал как ожидается следующий код:
//
// foo_says(get_foo("Hello!"));

struct Bar : public Foo {
    Bar(const char *msg) : Foo(msg) {}
};

Bar get_foo(const char *msg) { return Bar(msg); }

int main() {}
