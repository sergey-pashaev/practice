#include <cstdint>
#include <cstdlib>
#include <iostream>

uint64_t naive_gcd(uint64_t a, uint64_t b) {
    uint64_t gcd = 1;
    for (uint64_t d = 2; d < std::max(a, b); ++d) {
        if ((a % d == 0) && (b % d == 0)) gcd = d;
    }
    return gcd;
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

    std::cout << naive_gcd(a, b) << '\n';

    return 0;
}
