// frequency queries

// You are given q queries. Each query is of the form two integers
// described below:

// - 1 x : Insert x in your data structure.
// - 2 y : Delete one occurence of y from your data structure, if
//   present.
// - 3 z : Check if any integer is present whose frequency is exactly
//   z.  If yes, print 1 else 0.

// The queries are given in the form of a 2-D array queries of size q
// where queries[i][0] contains the operation, and queries[i][1]
// contains the data element. For example, you are given array queries
// = [(1, 1), (2, 2), (3, 2), (1, 1), (1, 1), (2, 1), (3, 2)]. The
// results of each operation are:

// Operation   Array   Output
// (1,1)       [1]
// (2,2)       [1]
// (3,2)                   0
// (1,1)       [1,1]
// (1,1)       [1,1,1]
// (2,1)       [1,1]
// (3,2)                   1

// Return an array with the output: [0, 1].

// Function Description

// Complete the freqQuery function in the editor below. It must return
// an array of integers where each element is a 1 if there is at least
// one element value with the queried number of occurrences in the
// current array, or 0 if there is not.

// freqQuery has the following parameter(s):

// queries: a 2-d array of integers

#include <catch2/catch.hpp>

#include <unordered_map>
#include <vector>

using namespace std;

struct Index {
    // value -> count
    unordered_map<int, int> count;

    // freq -> count
    unordered_map<int, int> freq;
};

vector<int> freq_queries(const vector<vector<int>>& queries) {
    vector<int> ret;

    Index idx;

    for (auto& query : queries) {
        int cmd = query[0];
        int v = query[1];

        if (cmd == 1) {
            // insert
            if (idx.count[v] > 0) {
                // decrease frequency of prev count
                --idx.freq[idx.count[v]];
            }

            // increase count
            ++idx.count[v];

            // increase frequency of current count
            ++idx.freq[idx.count[v]];
        } else if (cmd == 2) {
            // delete
            if (idx.count[v] > 0) {
                // decrease frequency of current count
                --idx.freq[idx.count[v]];

                // lower count
                --idx.count[v];
                if (idx.count[v] > 0) {
                    // increase freq of current count
                    ++idx.freq[idx.count[v]];
                }
            }
        } else if (cmd == 3) {
            // check freq
            ret.push_back((idx.freq[v] > 0 ? 1 : 0));
        }
    }

    return ret;
}

TEST_CASE("frequency queries") {
    REQUIRE(freq_queries({{1, 5},
                          {1, 6},
                          {3, 2},
                          {1, 10},
                          {1, 10},
                          {1, 6},
                          {2, 5},
                          {3, 2}}) == vector<int>{0, 1});

    REQUIRE(freq_queries({{3, 4}, {2, 1003}, {1, 16}, {3, 1}}) ==
            vector<int>{0, 1});

    REQUIRE(freq_queries({{1, 3},
                          {2, 3},
                          {3, 2},
                          {1, 4},
                          {1, 5},
                          {1, 5},
                          {1, 4},
                          {3, 2},
                          {2, 4},
                          {3, 2}}) == vector<int>{0, 1, 1});

    REQUIRE(freq_queries({{2, 3}, {2, 3}, {2, 3}, {3, 0}}) == vector<int>{0});
}
