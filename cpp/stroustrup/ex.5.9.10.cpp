#include <iostream>

using namespace std;

void Print(char months[][12]) {
    for (int i = 0; i < 12; ++i) {
        cout << months[i] << endl;
    }
}

int main() {
    char months[][12] = {"january",   "february", "march",    "april",
                         "may",       "june",     "july",     "august",
                         "september", "october",  "november", "december"};

    Print(months);
}
