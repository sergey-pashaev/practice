// array manipulation

// Starting with a 1-indexed array of zeros and a list of operations,
// for each operation add a value to each of the array element between
// two given indices, inclusive. Once all operations have been
// performed, return the maximum value in your array.

// For example, the length of your array of zeros n = 10. Your list of
// queries is as follows:

// a b k
// 1 5 3
// 4 8 7
// 6 9 1

// Add the values of k between the indices a and b inclusive:

// index -> 1 2 3  4  5 6 7 8 9 10
// 	   [0,0,0, 0, 0,0,0,0,0, 0]
// 	   [3,3,3, 3, 3,0,0,0,0, 0]
// 	   [3,3,3,10,10,7,7,7,0, 0]
// 	   [3,3,3,10,10,8,8,8,1, 0]

// The largest value is after all operations are performed.

// Function Description

// Complete the function arrayManipulation in the editor below. It
// must return an integer, the maximum value in the resulting array.

// arrayManipulation has the following parameters:

// n - the number of elements in your array
// queries - a two dimensional array of queries where each queries[i] contains
// three integers, a, b, and k.

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

long do_query(const vector<int>& q, vector<long>& v) {
    int a = q[0] - 1;
    int b = q[1] - 1;
    int k = q[2];

    long max_v = v[a];

    for (int i = a; i <= b; ++i) {
        v[i] += k;
        if (v[i] > max_v) {
            max_v = v[i];
        }
    }

    return max_v;
}

long manipulation(int n, const vector<vector<int>>& queries) {
    vector<long> v(n, 0);
    long max = 0;

    for (auto& q : queries) {
        long t = do_query(q, v);
        if (t > max) {
            max = t;
        }
    }

    return max;
}

TEST_CASE("array manipulation") {
    REQUIRE(manipulation(5, {{1, 2, 100}, {2, 5, 100}, {3, 4, 100}}) == 200);
}
