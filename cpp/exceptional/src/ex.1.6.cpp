// ex.1.6

// Временные объекты

#include <algorithm>
#include <list>
#include <string>

#include <catch2/catch.hpp>

using namespace std;

struct Employee {
    operator string() const { return name; }

    string name;
    string addr;
};

// 1. args passed not by const ref
// 2. i != emps.end() - shouln't be evaluated on each iteration
// 3. ++i if more effective than i++
// 4. string(*i) - temporary object
string FindAddr(list<Employee> emps, string name) {
    for (list<Employee>::iterator i = emps.begin(); i != emps.end(); i++) {
        if (string(*i) == name) {
            return i->addr;
        }
    }
    return "";
}

string FindAddrFixed(const list<Employee>& emps, const string& name) {
    for (list<Employee>::const_iterator i = emps.begin(), end = emps.end();
         i != end; ++i) {
        if (i->name == name) {
            return i->addr;
        }
    }
    return "";
}

TEST_CASE("FindAddr") {
    list<Employee> emps = {{"name1", "addr1"}, {"name2", "addr2"}};
    REQUIRE(FindAddr(emps, "name1") == "addr1");
    REQUIRE(FindAddrFixed(emps, "name1") == "addr1");
}
