#include <iostream>
#include <map>
#include <string>

using namespace std;

bool is_anagrams(const string& s1, const string& s2) {
    map<char, int> m1;
    for (char c : s1) m1[c]++;

    map<char, int> m2;
    for (char c : s2) m2[c]++;

    return m1 == m2;
}

int main() {
    string s1;
    cin >> s1;

    string s2;
    cin >> s2;

    cout << static_cast<int>(is_anagrams(s1, s2)) << '\n';
    return 0;
}
