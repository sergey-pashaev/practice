// prima - algorithm to find graph with minimal sum of weights which
// connects all nodes

#include <catch2/catch.hpp>

#include <iostream>
#include <limits>
#include <set>
#include <utility>
#include <vector>

using namespace std;

// return number of closest not connected neighbor
int closest(const vector<int>& v, const set<int>& connected) {
    int min = numeric_limits<int>::max();
    int imin;
    const size_t n = v.size();
    for (size_t i = 0; i < n; ++i) {
        // skip zeros
        if (v[i] == 0) continue;

        if (v[i] < min && connected.count(i) == 0) {
            min = v[i];
            imin = i;
        }
    }

    return imin;
}

// return edges of minimam connected graph
vector<pair<int, int>> prima(const vector<vector<int>>& graph) {
    const int n = graph.size();

    set<int> connected;
    vector<pair<int, int>> edges;

    // pick random node
    int from = 0;

    // connect to closest
    int to = closest(graph[from], connected);
    connected.insert(from);
    connected.insert(to);
    edges.emplace_back(from, to);

    // connect next closest to connected until all nodes connected
    while (connected.size() < n) {
        int closest_from;
        int closest_to;
        int dist = numeric_limits<int>::max();
        for (int from : connected) {
            int to = closest(graph[from], connected);
            if (graph[from][to] < dist) {
                dist = graph[from][to];
                closest_from = from;
                closest_to = to;
            }
        }

        connected.insert(closest_from);
        connected.insert(closest_to);
        edges.emplace_back(closest_from, closest_to);
    }

    return edges;
}

TEST_CASE("prima algorithm") {
    vector<vector<int>> data = {
        {0, 120, 147, 142, 107, 81}, {120, 0, 132, 42, 157, 45},
        {147, 132, 0, 108, 66, 105}, {142, 42, 108, 0, 168, 61},
        {107, 157, 66, 168, 0, 112}, {81, 45, 105, 61, 112, 0}};

    auto edges = prima(data);
    int sum = 0;
    for (auto& e : edges) {
        int dist = data[e.first][e.second];
        cout << e.first << " -> " << e.second << ' ' << dist << '\n';
        sum += dist;
    }
    cout << sum << '\n';
    REQUIRE(sum == 339);
}
