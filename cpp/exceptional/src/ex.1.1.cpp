// ex.1.1

// Итераторы

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

using Date = string;

Date TodaysDate() { return "06/23/95"; }

int main() {
    vector<string> e;

    copy(istream_iterator<Date>(cin), istream_iterator<Date>(),
         back_inserter(e));

    vector<Date>::iterator first = find(e.begin(), e.end(), "01/01/95");

    vector<Date>::iterator last = find(e.begin(), e.end(), "12/31/95");

    // error #1 - last is not checked for == e.end()
    *last = "12/31/96";

    // error #2 - first might come after last, so [first, last) is not
    // correct range
    copy(first, last, ostream_iterator<Date>(cout, "\n"));

    // error #3 - modyfing rvalue of builtin type (Date*), use
    // 'e.end() - 1' instead, or e might be empty
    e.insert(--e.end(), TodaysDate());

    // error #4 iterators might be invalidated after insert
    copy(first, last, ostream_iterator<Date>(cout, "\n"));

    return 0;
}
