/* ex.2.4 */

/* Write an alternative version of squeeze(s1,s2) that deletes each */
/* character in s1 that matches any character in the string s2. */

#include <stdio.h>

int position(const char s[], char c) {
    for (int i = 0; s[i]; ++i) {
        if (s[i] == c) return i;
    }

    return -1;
}

void squeeze(char s1[], const char s2[]) {
    int i, j;
    for (i = 0, j = 0; s1[i]; ++i)
        if (position(s2, s1[i]) < 0) s1[j++] = s1[i];
    s1[j] = '\0';
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    squeeze(argv[1], argv[2]);
    printf("%s\n", argv[1]);
    return 0;
}
