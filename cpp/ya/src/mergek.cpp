#include <iostream>
#include <vector>

using namespace std;

int main() {
    int k;
    cin >> k;

    vector<int> v(101, 0);
    for (int i = 0; i < k; ++i) {
        int n;
        cin >> n;

        int x;
        while (n--) {
            cin >> x;
            v[x]++;
        }
    }

    for (int i = 0; i < 101; ++i) {
        while (v[i]) {
            cout << i << ' ';
            --v[i];
        }
    }

    return 0;
}
