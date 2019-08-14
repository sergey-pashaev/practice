#include <typeinfo>

struct Expression {};

bool check_equals(Expression const *left, Expression const *right) {
    return typeid(*left) == typeid(*right);
}

int main() {}
