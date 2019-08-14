#include <cassert>
#include <iostream>
using namespace std;

char* resize(const char* str, unsigned size, unsigned new_size) {
    char* p = new char[new_size];
    const size_t min = size < new_size ? size : new_size;
    for (size_t i = 0; i < min; ++i) {
        p[i] = str[i];
    }

    delete[] str;
    return p;
}

char* getline() {
    const size_t TRAILING_ZERO = 1;
    size_t buf_size = 1024;
    char* buf = new char[buf_size];
    char c = 0;
    size_t i = 0;
    while (cin.get(c) && c != '\n') {
        if (i >= buf_size - TRAILING_ZERO) {
            const size_t new_buf_size = buf_size * 2;
            buf = resize(buf, buf_size, new_buf_size);
            buf_size = new_buf_size;
        }

        buf[i++] = c;
    }

    buf[i] = 0;
    return buf;
}

int main() {
    char* line = getline();
    cout << line;
    delete[] line;
}
