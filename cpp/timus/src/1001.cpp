#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    long n;
    vector<double> vl;
    while (cin >> n) {
        vl.push_back(sqrt(static_cast<double>(n)));
    }
    const int sz = vl.size();
    for (int i = sz - 1; i >= 0; --i) {
        cout << fixed;
        cout << setprecision(4);
        cout << '\n' << vl[i];
    }
    return 0;
}
