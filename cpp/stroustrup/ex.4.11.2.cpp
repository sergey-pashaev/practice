#include <complex>
#include <string>

int main() { return 0; }

// input
#if 1
char ch;
std::string s;
int count = 1;
const double pi = 3.14;
extern int error_number;
const char* name = "Name";
const char* season[] = {"spring", "summer", "fall", "winter"};

struct Date {
    int d, m, y;
};

int date(Date* p) { return p->d; }
double sqrt(double) throw();

template <class T>
T abs(T a) {
    return (a < 0) ? -a : a;
}

typedef std::complex<short> Point;
struct User;
enum Beer { Carlsberg, Tuborg, Thor };
namespace NS {
int a;
}
#endif

// declarations turned to definitions & definitions turned to declarations
void foo() {
    ch = 'x';
    s = "abc";
    NS::a = 1;
}

extern int count;
extern const double pi;
int error_number = 72;
extern const char* name;
extern const char* season[];
struct Date;
int date(Date* p);
double sqrt(double v) throw() { return v / 2; }
template <class T>
T abs(T a);
struct User {
    int x;
};

enum Beer;
