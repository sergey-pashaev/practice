// sorting bubble sort

// Consider the following version of Bubble Sort:

// for (int i = 0; i < n; i++) {

//     for (int j = 0; j < n - 1; j++) {
//         // Swap adjacent elements if they are in decreasing order
//         if (a[j] > a[j + 1]) {
//             swap(a[j], a[j + 1]);
//         }
//     }

// }

// Given an array of integers, sort the array in ascending order using
// the Bubble Sort algorithm above. Once sorted, print the following
// three lines:

// Array is sorted in numSwaps swaps., where numSwaps is the number of swaps
// that took place.

// First Element: firstElement, where firstElement is the first element in the
// sorted array.

// Last Element: lastElement, where lastElement is the last element in the
// sorted array.

// Hint: To complete this challenge, you must add a variable that
// keeps a running tally of all swaps that occur during execution.

// For example, given a worst-case but small array to sort: a= [6, 4, 1] we go
// through the following steps:

// swap    a
// 0       [6,4,1]
// 1       [4,6,1]
// 2       [4,1,6]
// 3       [1,4,6]

// It took 3 swaps to sort the array. Output would be

// Array is sorted in 3 swaps.
// First Element: 1
// Last Element: 6

// Function Description

// Complete the function countSwaps in the editor below. It should
// print the three lines required, then return.

// countSwaps has the following parameter(s):

// a: an array of integers .

#include <catch2/catch.hpp>

#include <iostream>
#include <vector>

using namespace std;

int bubble_sort(vector<int>& a) {
    int swaps = 0;
    const size_t n = a.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            if (a[i] > a[j]) {
                swap(a[i], a[j]);
                ++swaps;
            }
        }
    }

    return swaps;
}

void count_swaps(vector<int> a) {
    int swaps = bubble_sort(a);

    cout << "Array is sorted in " << swaps << " swaps.\n";
    cout << "First Element: " << a.front() << "\n";
    cout << "Last Element: " << a.back() << "\n";
}

TEST_CASE("sorting bubble sort") { count_swaps({6, 4, 1}); }
