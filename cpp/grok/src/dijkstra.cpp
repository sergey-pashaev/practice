#include <catch.hpp>

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

typedef std::string Name;
typedef int Cost;
typedef std::pair<Name, Cost> Edge;
typedef std::map<Name, std::vector<Edge>> Graph;
typedef std::map<Name, Cost> Costs;

Edge lowest_cost(const Costs& costs, const std::set<Name>& processed) {
    Edge lowest = {"", std::numeric_limits<Cost>::max()};
    for (const auto& kv : costs) {
        if (kv.second < lowest.second &&
            processed.find(kv.first) == processed.end()) {
            lowest = kv;
        }
    }

    return lowest;
}

std::vector<Name> dijkstra(const Graph& g, const Name& start, const Name& end) {
    // check start node exists
    auto it = g.find(start);
    if (it == g.end()) {
        // start node not found, return empty
        return {};
    }

    // init costs map with end cost & neighboors of start
    // init parents map with start node
    Costs costs;
    std::map<Name, Name> parents;
    costs[end] = std::numeric_limits<Cost>::max();  // +inf
    for (const Edge& e : it->second) {
        costs[e.first] = e.second;
        parents[e.first] = start;
    }

    std::set<Name> processed;

    // get lowest cost edge yet not processed
    Edge lowest = lowest_cost(costs, processed);
    while (!lowest.first.empty()) {
        Name node = lowest.first;
        Cost cost = lowest.second;

        // iterate over edge neighboors
        auto it = g.find(node);
        if (it != g.end()) {
            for (const Edge& e : it->second) {
                // calc new cost of path to neighboor through current lowest
                // cost edge
                Cost new_cost = cost + e.second;
                auto old_cost = costs.find(e.first);
                // if new cost is better - update costs & parents map
                if (old_cost == costs.end() ||
                    (old_cost != costs.end() && new_cost < old_cost->second)) {
                    costs[e.first] = new_cost;
                    parents[e.first] = node;
                }
            }
        }

        // mark node as processed
        processed.insert(node);

        // get lowest cost edge yet not processed
        lowest = lowest_cost(costs, processed);
    }

    // assemble path
    std::vector<Name> path;
    {
        auto it = parents.find(end);
        while (it != parents.end()) {
            path.push_back(it->first);
            it = parents.find(it->second);
        }
        path.push_back(start);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

void print_path(const char* prefix, const std::vector<Name>& path) {
    std::cout << prefix << '\n';
    for (const Name& e : path) {
        std::cout << e << ' ';
    }
    std::cout << '\n';
}

TEST_CASE("dijkstra") {
    SECTION("simple") {
        Graph g = {
            {"start", {{"a", 6}, {"b", 2}}},
            {"b", {{"a", 3}, {"end", 5}}},
            {"a", {{"end", 1}}},
        };

        auto path = dijkstra(g, "start", "end");
        print_path("simple", path);
    }

    SECTION("ex 7.1 a") {
        Graph g = {
            {"start", {{"a", 5}, {"c", 2}}},
            {"c", {{"a", 8}, {"d", 7}}},
            {"a", {{"b", 4}, {"d", 2}}},
            {"b", {{"end", 3}, {"d", 6}}},
            {"d", {{"end", 1}}},
        };

        auto path = dijkstra(g, "start", "end");
        print_path("ex 7.1 a", path);
    }

    SECTION("ex 7.1 b") {
        Graph g = {
            {"start", {{"a", 10}}},
            {"a", {{"b", 20}}},
            {"b", {{"c", 1}, {"end", 30}}},
            {"c", {{"a", 1}}},
        };

        auto path = dijkstra(g, "start", "end");
        print_path("ex 7.1 b", path);
    }
}
