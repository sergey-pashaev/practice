void f(char) {}
void g(char&) {}
void h(const char&) {}

int main() {
    char c = 21;
    unsigned char uc = 22;
    signed char sc = -5;

    f('a');  // temp char
    // g('a'); // err
    h('a');

    f(49);  // temp char
    // g(49); // err
    h(49);

    // f(3300); // err
    // g(3300); // err
    // h(3300); // err

    f(c);  // temp char
    g(c);
    h(c);

    f(uc);  // temp char
    // g(uc); // err
    h(uc);

    f(sc);  // temp char
    // g(sc); // err
    h(sc);
}
