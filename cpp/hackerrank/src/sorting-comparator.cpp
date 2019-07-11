// sorting comparator

// Comparators are used to compare two objects. In this challenge,
// you'll create a comparator and use it to sort an array. The Player
// class is provided in the editor below. It has two fields:

// : name a string.
// : score an integer.

// Given an array of n Player objects, write a comparator that sorts
// them in order of decreasing score. If 2 or more players have the same
// score, sort those players alphabetically ascending by name. To do
// this, you must create a Checker class that implements the
// Comparator interface, then write an int compare(Player a, Player b)
// method implementing the Comparator.compare(T o1, T o2) method. In
// short, when sorting in ascending order, a comparator function
// returns -1 if a < b, 0 if a == b and 1 if a > b.

// For example, given n = 3 Player objects with Player.name,
// Player.score values of data = [[Smith, 20], [Jones, 15], [Jones,
// 20]], we want to sort the list as data_sorted = [[Jones, 20],
// [Smith, 20], [Jones, 15]].

// Function Description

// Declare a Checker class that implements the comparator method as
// described. It should sort first descending by score, then ascending
// by name. The code stub reads the input, creates a list of Player
// objects, uses your method to sort the data, and prints it out
// properly.

#include <catch2/catch.hpp>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Player {
    int score;
    string name;
};

class Checker {
   public:
    static int comparator(Player a, Player b) {
        return (a.score > b.score || (a.score == b.score && a.name < b.name))
                   ? 1
                   : -1;
    }
};

TEST_CASE("sorting comparator") {
    vector<Player> players = {
        {20, "davis"}, {15, "davis"}, {10, "davis"}, {15, "edge"}, {15, "amy"}};

    sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.score > b.score || (a.score == b.score && a.name < b.name);
    });

    for (Player& p : players) {
        cout << p.score << ' ' << p.name << '\n';
    }
}
