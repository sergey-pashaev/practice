// fraudulent activity notifications

// HackerLand National Bank has a simple policy for warning clients
// about possible fraudulent account activity. If the amount spent by
// a client on a particular day is greater than or equal to 2x the
// client's median spending for a trailing number of days, they send
// the client a notification about potential fraud. The bank doesn't
// send the client any notifications until they have at least that
// trailing number of prior days' transaction data.

// Given the number of trailing days d and a client's total daily
// expenditures for a period of days, find and print the number of
// times the client will receive a notification over all n days.

// For example, d = 3 and expenditures = [10, 20, 30, 40, 50]. On the
// first three days, they just collect spending data. At day 4, we
// have trailing expenditures of [10, 20, 30]. The median is 20 and
// the day's expenditure is 40. Because 40 >= 2 * 20, there will be a
// notice. The next day, our trailing expenditures are [20, 30, 40]
// and the expenditures are 50. This is less than 2 * 30 so no notice
// will be sent. Over the period, there was one notice sent.

// Function Description

// Complete the function activityNotifications in the editor below. It
// must return an integer representing the number of client
// notifications.

// activityNotifications has the following parameter(s):

// expenditure: an array of integers representing daily expenditures
// d: an integer, the lookback days for median spending

#include <catch2/catch.hpp>

#include <vector>

using namespace std;

double median(vector<int>& count, int d) {
    int m1 = -1;
    int m2 = -1;
    if (d % 2 == 0) {
        for (int j = 0, sum = 0; j < 201; ++j) {
            sum += count[j];
            if (m1 < 0 && sum >= d / 2) {
                m1 = j;
            }

            if (m2 < 0 && sum >= d / 2 + 1) {
                m2 = j;
                break;
            }
        }
    } else {
        for (int j = 0, sum = 0; j < 201; ++j) {
            sum += count[j];
            if (sum > d / 2) {
                m1 = m2 = j;
                break;
            }
        }
    }

    return (m1 + m2) / 2.0;
}

int notifications(vector<int> exp, int d) {
    vector<int> count(201, 0);
    // use counting sort for expected range of numbers
    for (int i = 0; i < d; ++i) {
        count[exp[i]]++;
    }

    int notifications = 0;
    const int n = exp.size();
    for (int i = d; i < n; ++i) {
        double m = median(count, d);

        if (exp[i] >= m * 2) {
            ++notifications;
        }

        count[exp[i]]++;
        count[exp[i - d]]--;
    }

    return notifications;
}

TEST_CASE("fraudulent-activity-notifications") {
    REQUIRE(notifications({10, 20, 30, 40, 50}, 3) == 1);
    REQUIRE(notifications({1, 2, 3, 4, 4}, 4) == 0);
    REQUIRE(notifications({2, 3, 4, 2, 3, 6, 8, 4, 5}, 5) == 2);
}
