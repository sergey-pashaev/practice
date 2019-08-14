#include <iostream>
using namespace std;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void sh(int a[], unsigned size) {
    cout << "sh\n";
    for (unsigned i = 0; i < size - 1; ++i) {
        cout << i << ' ' << ((i + size - 1) % size) << '\n';
        swap(a + i, a + ((i + size - 1) % size));
        for (int y = 0; y < size; ++y) {
            cout << a[y] << ' ';
        }
        cout << '\n';
    }
}

void rotate(int a[], unsigned size, int shift) {
    for (; shift > 0; --shift) {
        sh(a, size);
    }
}
// for (unsigned i = 0 + shift; i < size - shift; ++i) {
//     cout << i << ' ' << ((i + shift) % size) << '\n';
//     swap(a + i, a + ((i + shift) % size));
//     for (int y = 0; y < size; ++y) {
//         cout << a[y] << ' ';
//     }
//     cout << '\n';
// }

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    unsigned size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < size; ++i) {
        cout << i << ' ';
    }
    cout << "\n\n";

    for (int i = 0; i < size; ++i) {
        cout << arr[i] << ' ';
    }
    cout << '\n';

    rotate(arr, size, 2);

    // for (int i = 0; i < size; ++i) {
    //     cout << arr[i] << ' ';
    // }
    // cout << '\n';
}
