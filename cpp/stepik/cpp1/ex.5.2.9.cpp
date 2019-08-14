#include <cstddef>  // size_t

struct String {
    String(const char *str = "");
    String(size_t n, char c);
    ~String();

    String(const String &other);
    String &operator=(const String &other);

    void append(const String &other);

    struct Proxy {
        Proxy(const String &s, size_t i) : s(s), i(i) {}

        String operator[](size_t j) const {
            String ret;
            for (size_t idx = 0; idx < j - i; ++idx) {
                ret.append(String(1, *(s.str + i + idx)));
            }
            return ret;
        }

        const String &s;
        size_t i;
    };

    Proxy operator[](size_t i) const { return Proxy(*this, i); }

    size_t size;
    char *str;
};

int main() {}
