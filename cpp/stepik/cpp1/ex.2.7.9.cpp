#include <cassert>
#include <cstddef>
#include <iomanip>
#include <iostream>
using namespace std;

int** make_array_2d(size_t rows, size_t columns) {
    int** arr = new int*[rows];
    arr[0] = new int[rows * columns];
    for (size_t i = 1; i < rows; ++i) {
        arr[i] = arr[i - 1] + columns;
    }
    return arr;
}

void print_array_2d(int** arr, size_t rows, size_t columns) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            cout << setfill(' ') << setw(3) << arr[i][j] << ' ';
        }
        cout << '\n';
    }
}

void enum_array_2d(int** arr, size_t rows, size_t columns) {
    int v = 0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            arr[i][j] = v++;
        }
    }
}

void free_array_2d(int** arr, size_t, size_t) {
    delete[] arr[0];
    delete[] arr;
}

int** transpose(const int* const* m, unsigned rows, unsigned cols) {
    int** arr = make_array_2d(cols, rows);
    for (size_t i = 0; i < cols; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            arr[i][j] = m[j][i];
        }
    }
    return arr;
}

int main() {
    const size_t rows = 3;
    const size_t columns = 6;
    int** arr = make_array_2d(rows, columns);
    enum_array_2d(arr, rows, columns);
    print_array_2d(arr, rows, columns);
    int** transposed = transpose(arr, rows, columns);
    cout << '\n';
    print_array_2d(transposed, columns, rows);

    free_array_2d(transposed, columns, rows);
    free_array_2d(arr, rows, columns);
}
