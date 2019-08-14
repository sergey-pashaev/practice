#include <iostream>
#include <typeinfo>

void print_values(std::ostream&) {}

template <typename T, typename... Args>
void print_values(std::ostream& os, const T& value, const Args... args) {
    os << typeid(value).name() << ": " << value << '\n';
    print_values(os, args...);
}

int main() {}
