#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    vector<pair<string, int>> v = {
        {"Alice", 85},
        {"Bob", 62},
        {"Charlie", 91},
        {"Diana", 74},
        {"Eve", 62}
    };

    // Sort by second (the integer), ascending
    sort(v.begin(), v.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second < b.second;
         });

    cout << "Sorted by integer (ascending):" << endl;
    for (const auto& p : v) {
        cout << p.first << " : " << p.second << endl;
    }

    return 0;
}