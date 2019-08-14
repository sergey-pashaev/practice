#include <string>

using namespace std;

#define UNUSED(x) (void)(x)

int main() {
    char c = 'c';
    char* pc = &c;
    UNUSED(pc);
    int iarr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int(&rarr)[10] = iarr;
    UNUSED(rarr);
    string sarr[] = {"abc", "def"};
    string(*psarr)[2] = &sarr;
    UNUSED(psarr);
    char** ppc = &pc;
    UNUSED(ppc);
    const int x = 42;
    const int* px = &x;
    UNUSED(px);
    int d = 10;
    int* const pd = &d;
    UNUSED(pd);
}
