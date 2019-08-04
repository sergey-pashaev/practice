// generate parentheses

// Дано целое число n. Требуется вывести все правильные скобочные
// последовательности длины 2n, упорядоченные лексикографически
// (см. https://ru.wikipedia.org/wiki/Лексикографический_порядок). В
// задаче используются только круглые скобки.

#include <iostream>
#include <string>

using namespace std;

void generate(int n, string s, int o, int c) {
    if (o + c > 2 * n) return;

    if (o == c && o + c == 2 * n) {
        cout << s << '\n';
    }

    if (o < n) {
        // add open
        generate(n, s + '(', o + 1, c);
    }

    if (c < o) {
        // add closed
        generate(n, s + ')', o, c + 1);
    }
}

void generate(int n) { generate(n, string(), 0, 0); }

int main() {
    int n;
    cin >> n;

    generate(n);

    return 0;
}
