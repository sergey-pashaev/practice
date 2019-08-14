#include <map>
#include <sstream>
#include <string>

#include <catch2/catch.hpp>

using namespace std;

struct Data {
    Data() : cnt(0), sum(0), avg(0) {}

    int cnt;
    double sum;
    double avg;
};

void Calculate(istringstream &in, map<string, Data> &data) {
    string word;
    double value;
    while (in >> word && in >> value) {
        Data &rec = data[word];
        rec.cnt++;
        rec.sum += value;
    }

    Data all;
    for (auto &kv : data) {
        kv.second.avg = kv.second.sum / kv.second.cnt;
        all.sum += kv.second.sum;
        all.cnt += kv.second.cnt;
    }

    all.avg = all.sum / all.cnt;
    data["_all"] = all;
}

TEST_CASE("ex.6.6.3") {
    istringstream in{"Dave 5.0 Mike 1.5 John 3.2 Mike 7.9 John 12.1"};

    map<string, Data> data;
    Calculate(in, data);

    REQUIRE(data["_all"].sum == Approx(29.7));
    REQUIRE(data["_all"].avg == Approx(5.94));

    REQUIRE(data["Dave"].sum == Approx(5.0));
    REQUIRE(data["Dave"].avg == Approx(5.0));

    REQUIRE(data["Mike"].sum == Approx(9.4));
    REQUIRE(data["Mike"].avg == Approx(4.7));

    REQUIRE(data["John"].sum == Approx(15.3));
    REQUIRE(data["John"].avg == Approx(7.65));
}
