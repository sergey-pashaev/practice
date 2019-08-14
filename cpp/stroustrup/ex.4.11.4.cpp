#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

int main() {
    for (char c = ' '; c < std::numeric_limits<char>::max(); ++c) {
        cout << c << " " << setw(3) << dec << (int)c << " 0x" << setw(2) << hex
             << (int)c << endl;
    }

    return 0;
}
