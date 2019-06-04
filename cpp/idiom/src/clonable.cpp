#include "clonable.h"

#include <iostream>
#include <memory>

struct Concrete1 : public psv::CloneInherit<Concrete1, psv::Clonable> {
    Concrete1() { std::cout << "concrete1 ctor\n"; }
    Concrete1(const Concrete1&) { std::cout << "concrete1 copy ctor\n"; }
};

int main() {
    auto c = std::make_unique<Concrete1>();
    auto cc = c->Clone();
    return 0;
}
