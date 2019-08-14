void strcat(char *to, const char *from) {
    for (; *to; ++to)
        ;
    while ((*to++ = *from++))
        ;
}

int main() {}
