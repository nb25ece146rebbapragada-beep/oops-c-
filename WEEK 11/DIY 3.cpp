#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, int> freq;
    string word;

    cout << "Enter words (Ctrl+D on Linux/Mac or Ctrl+Z then Enter on Windows to stop):" << endl;

    while (cin >> word) {
        freq[word]++;
    }

    if (freq.empty()) {
        cout << "No words entered." << endl;
        return 0;
    }

    cout << "\nWord counts:" << endl;
    for (const auto& pair : freq) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // Find the most frequent word
    string mostFrequent;
    int maxCount = 0;
    for (const auto& pair : freq) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequent = pair.first;
        }
    }

    cout << "\nMost frequent word: " << mostFrequent
         << " (" << maxCount << " times)" << endl;

    return 0;
}