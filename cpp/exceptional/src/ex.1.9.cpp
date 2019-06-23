// ex.1.9

// Предикаты. Часть 1

#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

#include <catch2/catch.hpp>

using namespace std;

// 1. algorithm 'remove' moves to be deleted values to the end of
// sequnce and returns iterator to furst such item.

// 2. remove all 3s from vector of ints
TEST_CASE("remove 3s") {
    vector<int> vi = {1, 2, 3, 4, 3, 5, 6, 3, 7};
    vi.erase(remove(vi.begin(), vi.end(), 3), vi.end());
    REQUIRE(find(vi.begin(), vi.end(), 3) == vi.end());
}

// 3. implement missing parts
template <typename FwdIter>
FwdIter remove_nth(FwdIter first, FwdIter last, std::size_t n) {
    // missing code:
    assert(distance(first, last) >= n);

    // skip to n element
    advance(first, n);

    // overwrite n element & shift rest of sequence
    while (first != last) {
        *first = *(first + 1);
        ++first;
    }

    // element to delete
    return last - 1;
}

template <typename FwdIter>
FwdIter remove_nth_book(FwdIter first, FwdIter last, std::size_t n) {
    // missing code:
    assert(distance(first, last) >= n);

    // skip to n element
    advance(first, n);

    if (first != last) {
        FwdIter dest = first;
        return copy(++first, last, dest);
    }

    return last;
}

TEST_CASE("remove_nth") {
    vector<int> vi = {1, 2, 3, 4, 5};

    // remove 2
    auto r = remove_nth(vi.begin(), vi.end(), 1);
    vi.erase(r, vi.end());
    REQUIRE(find(vi.begin(), vi.end(), 2) == vi.end());
    REQUIRE(vi.size() == 4);

    // remove 1
    vi.erase(remove_nth(vi.begin(), vi.end(), 0), vi.end());
    REQUIRE(find(vi.begin(), vi.end(), 1) == vi.end());
    REQUIRE(vi.size() == 3);

    // remove 5
    vi.erase(remove_nth(vi.begin(), vi.end(), 2), vi.end());
    REQUIRE(find(vi.begin(), vi.end(), 5) == vi.end());
    REQUIRE(vi.size() == 2);
}
