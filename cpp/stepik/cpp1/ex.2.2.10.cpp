#include <iostream>

using namespace std;

void reverse() {
    int x = 0;
    if (cin >> x && x) reverse();
    if (x) cout << x << ' ';
}

int main() {
    reverse();
    return 0;
}
