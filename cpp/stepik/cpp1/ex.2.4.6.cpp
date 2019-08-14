unsigned strlen(const char *str) {
    unsigned size = 0;
    while (*str++) ++size;
    return size;
}

int main() {}
