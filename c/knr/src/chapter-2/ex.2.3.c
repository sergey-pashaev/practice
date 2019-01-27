/* ex.2.3 */

/* Write a function htoi(s), which converts a string of hexadecimal */
/* digits (including an optional 0x or 0X ) into its equivalent integer */
/* value. The allowable digits are 0 through 9, a through f, and A */
/* through F. */

#include <stdio.h>

int hexval(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'f')
        return 10 + c - 'a';
    else if (c >= 'A' && c <= 'F')
        return 10 + c - 'A';
    return 0;
}

int htoi(const char s[]) {
    int n = 0;
    const int base = 16;

    int i = 0;
    while (s[i]) {
        if (s[i] == '0' && (s[i + 1] == 'X' || s[i + 1] == 'x')) {
            i += 2;
        } else {
            n = base * n + hexval(s[i++]);
        }
    }

    return n;
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    printf("%u\n", htoi(argv[1]));
    return 0;
}
