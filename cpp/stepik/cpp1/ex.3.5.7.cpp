struct Cls {
    Cls(char c, double d, int i);

   private:
    char c;
    double d;
    int i;
};

struct Twin {
    char c;
    double d;
    int i;
};

// Эта функция должна предоставить доступ к полю c объекта cls.
// Обратите внимание, что возвращается ссылка на char, т. е.
// доступ предоставляется на чтение и запись.
char &get_c(Cls &cls) {
    /* ... */
    Twin &t = (Twin &)cls;
    return t.c;
}

// Эта функция должна предоставить доступ к полю d объекта cls.
// Обратите внимание, что возвращается ссылка на double, т. е.
// доступ предоставляется на чтение и запись.
double &get_d(Cls &cls) {
    /* ... */
    Twin &t = (Twin &)cls;
    return t.d;
}

// Эта функция должна предоставить доступ к полю i объекта cls.
// Обратите внимание, что возвращается ссылка на int, т. е.
// доступ предоставляется на чтение и запись.
int &get_i(Cls &cls) {
    /* ... */
    Twin &t = (Twin &)cls;
    return t.i;
}

int main() {}
