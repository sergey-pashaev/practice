#include <cstdint>
#include <cstdlib>
#include <iostream>

uint64_t euclid_gcd(uint64_t a, uint64_t b) {
    if (!a) return b;
    if (!b) return a;
    if (a >= b) return euclid_gcd(a % b, b);
    if (b >= a) return euclid_gcd(a, b % a);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <number 1> <number 2>\n";
        return 1;
    }

    uint64_t a = std::atoll(argv[1]);
    uint64_t b = std::atoll(argv[2]);
    if (!a || !b) {
        std::cout << "error: not a number\n";
        return 1;
    }

    std::cout << euclid_gcd(a, b) << '\n';

    return 0;
}
