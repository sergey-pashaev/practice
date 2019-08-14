#include <cassert>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

void append(char* other_str, size_t other_size) {
    char* str = new char[6];
    strcpy(str, "Hello");
    size_t size = strlen(str);
    cout << str << '\n';

    size_t new_size = size + other_size + 1;
    char* buf = new char[new_size];
    strncpy(buf, str, size);
    strncpy(buf + size, other_str, other_size);
    buf[new_size] = 0;
    size = new_size;
    delete[] str;
    str = buf;

    cout << buf << '\n';
}

int main() {
    char* str = new char[12];
    strcpy(str, "xxxHelloxxx");

    append(str, strlen(str));
}
