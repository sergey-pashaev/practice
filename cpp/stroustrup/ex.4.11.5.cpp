#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

template <typename T>
void PrintLimits(const char* name) {
    cout << numeric_limits<T>::min() << " <= " << name
         << " <= " << numeric_limits<T>::max() << endl;
}

template <>
void PrintLimits<char>(const char* name) {
    cout << dec << (int)numeric_limits<char>::min() << " <= " << name
         << " <= " << dec << (int)numeric_limits<char>::max() << endl;
}

#define STR(S) #S
#define PRINT_LIMITS(T) PrintLimits<T>(STR(T))

int main() {
    PRINT_LIMITS(char);
    PRINT_LIMITS(short);
    PRINT_LIMITS(int);
    PRINT_LIMITS(long);
    PRINT_LIMITS(float);
    PRINT_LIMITS(double);
    PRINT_LIMITS(long double);
    PRINT_LIMITS(unsigned);
}
