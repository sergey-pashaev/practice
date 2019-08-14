#include <algorithm>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include <catch2/catch.hpp>

using namespace std;

template <typename T>
class RunningMedian {
   public:
    void AddValue(T v) {
        if (lowers.empty() || v < lowers.top()) {
            lowers.push(v);
        } else {
            highers.push(v);
        }

        Rebalance();
    }

    double GetMedian() const {
        if (lowers.size() == highers.size()) {
            return ((double)lowers.top() + (double)highers.top()) / 2;
        }

        return lowers.size() < highers.size() ? highers.top() : lowers.top();
    }

   private:
    void Rebalance() {
        // todo:
        // clang-format off
        // auto smaller_heap = (lowers.size() < highers.size()) ? &lowers : &highers;
        // auto bigger_heap  = (lowers.size() < highers.size()) ? &highers : &lowers;
        // clang-format on

        if (lowers.size() < highers.size()) {
            if (highers.size() - lowers.size() >= 2) {
                lowers.push(highers.top());
                highers.pop();
            }
        } else {
            if (lowers.size() - highers.size() >= 2) {
                highers.push(lowers.top());
                lowers.pop();
            }
        }
    }

    // maxheap - biggest element at the top
    priority_queue<T> lowers;

    // minheap - smallest element at the top
    priority_queue<T, vector<T>, greater<T>> highers;
};

struct Data {
    Data() : cnt(0), sum(0), avg(0) {}

    int cnt;
    double sum;
    double avg;
    RunningMedian<double> rmedian;
};

void Calculate(istringstream &in, map<string, Data> &data) {
    string word;
    double value;

    Data all;
    while (in >> word && in >> value) {
        Data &rec = data[word];
        rec.cnt++;
        rec.sum += value;
        rec.rmedian.AddValue(value);

        all.sum += value;
        all.cnt++;
        all.rmedian.AddValue(value);
    }

    for (auto &kv : data) {
        kv.second.avg = kv.second.sum / kv.second.cnt;
    }
    all.avg = all.sum / all.cnt;

    data["_all"] = all;
}

TEST_CASE("running median algorithm") {
    RunningMedian<double> rmedian;

    SECTION("odd size") {
        vector<int> values{1, 2, 4, 6, 22, 200, 201};
        random_shuffle(values.begin(), values.end());

        for (const auto &v : values) {
            rmedian.AddValue(v);
        }

        REQUIRE(rmedian.GetMedian() == 6);
    }

    SECTION("even size") {
        vector<int> values{12, 16, 18, 22, 23, 200, 201, 204};
        random_shuffle(values.begin(), values.end());

        for (const auto &v : values) {
            rmedian.AddValue(v);
        }

        REQUIRE(rmedian.GetMedian() == Approx(22.5));
    }

    SECTION("doubles") {
        vector<double> values{5.0, 1.5, 3.2, 7.9, 12.1, 10.0, 5.0};

        for (const auto &v : values) {
            rmedian.AddValue(v);
        }

        REQUIRE(rmedian.GetMedian() == Approx(5.0));
    }
}

TEST_CASE("ex.6.6.12") {
    istringstream in{
        "Dave 5.0 Mike 1.5 John 3.2 Mike 7.9 John 12.1 Mike 10.0 Mike 5.0"};

    map<string, Data> data;
    Calculate(in, data);

    REQUIRE(data["_all"].sum == Approx(44.7));
    REQUIRE(data["_all"].avg == Approx(6.38571428571));
    REQUIRE(data["_all"].rmedian.GetMedian() == Approx(5.0));

    REQUIRE(data["Dave"].sum == Approx(5.0));
    REQUIRE(data["Dave"].avg == Approx(5.0));
    REQUIRE(data["Dave"].rmedian.GetMedian() == Approx(5.0));

    REQUIRE(data["Mike"].sum == Approx(24.4));
    REQUIRE(data["Mike"].avg == Approx(6.1));
    REQUIRE(data["Mike"].rmedian.GetMedian() == Approx(6.45));

    REQUIRE(data["John"].sum == Approx(15.3));
    REQUIRE(data["John"].avg == Approx(7.65));
    REQUIRE(data["John"].rmedian.GetMedian() == Approx(7.65));
}
