#include <iostream>

using namespace std;

template <class T>
void PrintSize(const char* name) {
    cout << sizeof(T) << " bytes in " << name << endl;
}

#define STR(S) #S
#define PRINT_SIZE(T) PrintSize<T>(STR(T));

int main() {
    // fundamental types
    PRINT_SIZE(bool);

    PRINT_SIZE(char);
    PRINT_SIZE(unsigned char);
    PRINT_SIZE(signed char);

    PRINT_SIZE(wchar_t);
    PRINT_SIZE(/* signed */  wchar_t);
    PRINT_SIZE(/* unsigned */ wchar_t);

    PRINT_SIZE(short)
    PRINT_SIZE(unsigned short)
    PRINT_SIZE(signed short)

    PRINT_SIZE(int);
    PRINT_SIZE(unsigned int);
    PRINT_SIZE(signed int);

    PRINT_SIZE(long);
    PRINT_SIZE(unsigned long);
    PRINT_SIZE(signed long);

    PRINT_SIZE(long long);
    PRINT_SIZE(unsigned long long);
    PRINT_SIZE(signed long long);

    PRINT_SIZE(float);
    PRINT_SIZE(double);
    PRINT_SIZE(long double);

    // several pointer types
    PRINT_SIZE(int*);
    PRINT_SIZE(double*);
    PRINT_SIZE(double&);

    // arrays
    PRINT_SIZE(char[10]);
    PRINT_SIZE(int[10]);

    // several enums
    enum Keyword { ASM, AUTO, BREAK };
    PRINT_SIZE(Keyword);

    enum Big { BIGA = 0, BIGB = 100000000000, BIGC };
    PRINT_SIZE(Big);
    return 0;
}
