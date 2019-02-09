/* ex.4.1 */

/* Write the function strindex(s,t) which returns the position of the */
/* rightmost occurrence of t in s, or -1 if there is none. */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strindex(const char* s, const char* t) {
    int i, j, k;
    size_t len = strlen(s);
    for (i = len - 1; i >= 0; --i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k)
            ;
        if (k > 0 && t[k] == '\0') return i;
    }

    return -1;
}

int tests() {
    /* empty line */
    assert(strindex("", "d") == -1);

    /* empty pattern */
    assert(strindex("a", "") == -1);

    /* single char line & pattern: not found */
    assert(strindex("a", "d") == -1);

    /* multi char line & pattern: not found */
    assert(strindex("abc", "def") == -1);

    /* single char line & pattern: match  */
    assert(strindex("a", "a") == 0);

    /* multi char line & single char pattern: match */
    assert(strindex("abcdefg", "d") == 3);

    /* multi char line & single char pattern: multiple matches */
    assert(strindex("abcdefgdef", "d") == 7);

    /* multi char line & pattern: match */
    assert(strindex("abcdefg", "def") == 3);

    /* multi char line & pattern: multiple matches */
    assert(strindex("abcdefgdef", "def") == 7);

    return 0;
}

int usage(const char* bin) {
    printf("Usage: %s <string pattern>\n", bin);
    return 1;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        usage(argv[0]);
        return tests();
    }

    const char* pattern = argv[1];
    char* line = NULL;
    size_t len = 0;
    ssize_t nread;
    int found = 0;
    while ((nread = getline(&line, &len, stdin)) != -1) {
        int pos = strindex(line, pattern);
        if (pos >= 0) {
            printf("%d:%s", pos, line);
            ++found;
        }
    }

    free(line);
    return found;
}
