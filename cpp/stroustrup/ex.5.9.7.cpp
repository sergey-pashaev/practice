#include <iostream>

using namespace std;

const int kTrailingZero = 1;

struct MonthDay {
    int day;
    char month[9 + kTrailingZero];
};

int main() {
    // array approach
    char months[][12] = {"january",   "february", "march",    "april",
                         "may",       "june",     "july",     "august",
                         "september", "october",  "november", "december"};

    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int i = 0; i < 12; ++i) {
        cout << days[i] << " : " << months[i] << endl;
    }

    cout << endl;

    // struct approach
    MonthDay md[12] = {{31, "january"}, {28, "february"}, {31, "march"},
                       {30, "april"},   {31, "may"},      {30, "june"},
                       {31, "july"},    {31, "august"},   {30, "september"},
                       {31, "october"}, {30, "november"}, {31, "december"}};

    for (int i = 0; i < 12; ++i) {
        cout << md[i].day << " : " << md[i].month << endl;
    }
}
