// ex.1.7

// Использование стандартной библиотеки (или ещё раз о временных
// объектах)

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

bool operator==(const Employee& e, const std::string& name) {
    return e.name == name;
}

bool operator==(const std::string& name, const Employee& e) {
    return e.name == name;
}

string FindAddrStl(const list<Employee>& emps, const string& name) {
    auto i = std::find(emps.begin(), emps.end(), name);
    if (i != emps.end()) {
        return i->addr;
    }
    return "";
}

TEST_CASE("FindAddr") {
    list<Employee> emps = {{"name1", "addr1"}, {"name2", "addr2"}};
    REQUIRE(FindAddrStl(emps, "name1") == "addr1");
}
