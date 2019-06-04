#include <catch2/catch.hpp>

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

typedef std::string Name;
typedef int Cost;
typedef int Weight;

struct Item {
    Name name;
    Cost cost;
    Weight weight;
};

typedef std::vector<Item> Items;

struct Cell {
    std::vector<Name> items;
    Cost cost;
};

std::vector<Name> knapsack(const Items& items, Weight max_weight) {
    // find min weight of items
    Weight min = std::numeric_limits<Weight>::max();
    for (const Item& i : items) {
        if (i.weight < min) {
            min = i.weight;
        }
    }

    std::vector<Weight> weights;
    for (int w = min; w <= max_weight; w += min) {
        weights.push_back(w);
    }

    Cell table[items.size() + 1][weights.size() + 1];

    for (std::size_t i = 0; i <= items.size(); ++i) {
        for (std::size_t j = 0; j <= weights.size(); ++j) {
            if (i == 0 || j == 0) {
                table[i][j].cost = 0;
            } else {
                if (items[i - 1].weight <= weights[j - 1]) {
                    const Item& cur = items[i - 1];
                    const Cell& prev_max = table[i - 1][j];
                    const Cell& free_space = table[i - 1][j - cur.weight/min];
                    if (cur.cost + free_space.cost > prev_max.cost) {
                        table[i][j].cost = cur.cost + free_space.cost;
                        table[i][j].items = free_space.items;
                        table[i][j].items.push_back(cur.name);
                    } else {
                        table[i][j] = table[i-1][j];
                    }
                } else {
                    table[i][j] = table[i - 1][j];
                }
            }
        }
    }

    for (int i = 1; i <= items.size(); ++i) {
        for (int j = 1; j <= weights.size(); ++j) {
            std::cout << items[i-1].name << "\t [" << i << "][" << j << "]:" << table[i][j].cost;
            std::cout << '(';
            for (std::size_t z = 0; z < table[i][j].items.size(); ++z) {
                std::cout << table[i][j].items[z] << ' ';
            }
            std::cout << ')';
            std::cout << "\n";
        }
        std::cout << '\n';
    }

    return {};
}

void knapsack(int limit, const std::vector<Weight>& weights,
              const std::vector<Cost>& costs, int n) {
    Cost table[n + 1][limit + 1];

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= limit; ++j) {
            if (i == 0 || j == 0) {
                table[i][j] = 0;
            } else if (weights[i - 1] <= j) {
                table[i][j] =
                    std::max(costs[i - 1] + table[i - 1][j - weights[i - 1]],
                             table[i - 1][j]);
            } else {
                table[i][j] = table[i - 1][j];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= limit; ++j) {
            std::cout << '[' << i << "][" << j << "]:" << table[i][j] << "\t\t";
        }
        std::cout << '\n';
    }
}

TEST_CASE("knapsack") {
    // std::vector<Weight> weights = {1, 3, 4};
    // std::vector<Cost> costs = {1500, 2000, 3000};
    // const int n = weights.size();
    // const int limit = 4;

    // knapsack(limit, weights, costs, n);

    Items items = {
        {"audio", 3000, 4}, {"notebook", 2000, 3}, {"guitar", 1500, 1}};

    knapsack(items, 4);
}
