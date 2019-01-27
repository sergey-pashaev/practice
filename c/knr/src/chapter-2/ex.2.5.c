/* ex.2.5 */

/* Write the function any(s1,s2), which returns the first location in */
/* a string s1 where any character from the string s2 occurs, or -1 if */
/* s1 contains no characters from s2.  (The standard library function */
/* strpbrk does the same job but returns a pointer to the location.) */

#include <stdio.h>

int any(const char s1[], const char s2[]) {
    for (int i = 0; s1[i]; ++i) {
        for (int j = 0; s2[j]; ++j) {
            if (s1[i] == s2[j]) return i;
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    printf("%d\n", any(argv[1], argv[2]));
    return 0;
}
