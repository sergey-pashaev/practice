#include <catch.hpp>

#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

typedef std::string Node;
typedef std::map<Node, std::vector<Node>> Graph;

bool bfs(const Graph& g, const Node& start, const Node& x) {
    std::queue<Node> q;
    q.push(start);

    std::set<Node> searched;

    while (!q.empty()) {
        // dequeue
        const Node& n = q.front();
        q.pop();

        // mark as searched
        searched.insert(n);

        if (n == x) {
            return true;
        } else {
            // add n's neighboors
            auto it = g.find(n);
            if (it != g.end()) {
                for (const Node& neighboor : it->second) {
                    // check node not in searched
                    if (searched.find(neighboor) == searched.end()) {
                        q.push(neighboor);
                    }
                }
            }
        }
    }

    return false;
}

TEST_CASE("bfs") {
    Graph g = {
        {"you", {"alice", "bob", "charlie"}},
        {"bob", {"anuj", "peggy"}},
        {"alice", {"peggy"}},
        {"claire", {"thom", "johny"}},
        {"anuj", {}},
        {"peggy", {}},
        {"thom", {}},
        {"johny", {}}};


    REQUIRE(bfs(g, "you", "anuj"));
    REQUIRE_FALSE(bfs(g, "anuj", "peggy"));
}
