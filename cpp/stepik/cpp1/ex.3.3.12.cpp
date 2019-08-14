#include <cstddef>  // size_t
#include <cstring>  // strlen, strcpy

struct String {
    String(const char *str = "");
    String(size_t n, char c);
    ~String();

    /* Реализуйте этот метод. */
    void append(String &other) {
        size_t new_size = size + other.size + 1;
        char *buf = new char[new_size];
        strncpy(buf, str, size);
        strncpy(buf + size, other.str, other.size);
        buf[new_size - 1] = 0;
        size = strlen(buf);
        delete[] str;
        str = buf;
    }

    size_t size;
    char *str;
};

int main() {}
