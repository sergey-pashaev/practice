#include <stdio.h>
#include <stdlib.h>

void stop() {
    printf("%s\n", __func__);
}

void bar(int x);

void foo(int x) {
    printf("%s %d\n", __func__, x);
    if (x == 0) {
        stop();
        return;
    }

    bar(x - 1);
}

void bar(int x) {
    printf("%s %d\n", __func__, x);
    if (x == 0) {
        stop();
        return;
    }

    foo(x - 1);
}

int usage(const char* bin) {
    printf("Usage: %s <n>\n", bin);
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return usage(argv[0]);
    }

    char* err = nullptr;
    int x = strtol(argv[1], &err, 10);
    if (*err != 0) {
        return usage(argv[0]);
    }

    foo(x);
    
    return 0;
}
