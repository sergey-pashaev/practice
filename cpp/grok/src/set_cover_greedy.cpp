#include <catch.hpp>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

typedef std::string Node;
typedef std::string Choice;
typedef std::map<Choice, std::set<Node>> Choices;

std::set<Node> set_cover(const Choices& choices, std::set<Node> needed) {
    std::set<Choice> ret;

    // loop while we need to cover some set
    while (!needed.empty()) {
        Choice best = "";
        std::set<Node> covered;

        // select choice which gives best current coverage
        for (const auto& kv : choices) {
            std::set<Node> new_covered;
            std::set_intersection(
                needed.begin(), needed.end(), kv.second.begin(),
                kv.second.end(),
                std::inserter(new_covered, new_covered.begin()));

            if (new_covered.size() > covered.size()) {
                covered = new_covered;
                best = kv.first;
            }
        }

        // put best choice to final set
        ret.insert(best);

        // remove part of set which is covered from needed to cover set
        std::set<Node> diff;
        std::set_difference(needed.begin(), needed.end(), covered.begin(),
                            covered.end(), std::inserter(diff, diff.begin()));
        needed = diff;
    }

    return ret;
}

TEST_CASE("set cover") {
    std::set<Node> needed = {"mt", "wa", "or", "id", "nv", "ut", "ca", "az"};

    Choices choices = {
        {"k1", {"id", "nv", "ut"}}, {"k2", {"id", "wa", "mt"}},
        {"k3", {"or", "nv", "ca"}}, {"k4", {"nv", "ut"}},
        {"k5", {"ca", "az"}},
    };

    std::set<Node> min = set_cover(choices, needed);
    for (const auto& e : min) {
        std::cout << e << ' ';
    }
    std::cout << '\n';
}
