#include <cassert>
#include <iostream>
using namespace std;

bool strfnd(const char *s1, const char *s2) {
    for (; (*s1 && *s2) && (*s1 == *s2); s1++, s2++)
        ;
    return *s2 == 0;
}

int strstr(const char *text, const char *pattern) {
    if (*pattern == 0) return 0;
    if (*text == 0) return -1;

    for (int i = 0; text[i]; ++i) {
        if (strfnd(text + i, pattern)) return i;
    }

    return -1;
}

int main() {
    assert(strfnd("", ""));
    assert(strfnd("1", ""));
    assert(strfnd("1", "1"));
    assert(strfnd("12", "12"));
    assert(strfnd("123", "123"));
    assert(strfnd("123", "12"));
    assert(!strfnd("23", "123"));
    assert(strfnd("23", "2"));

    assert(strstr("", "") == 0);
    assert(strstr("", "1") == -1);

    assert(strstr("1", "1") == 0);
    assert(strstr("12", "12") == 0);
    assert(strstr("123", "2") == 1);
    assert(strstr("1234", "23") == 1);
    assert(strstr("12323", "23") == 1);
}
