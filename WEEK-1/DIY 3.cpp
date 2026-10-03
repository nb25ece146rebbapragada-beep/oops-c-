#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    string sentence;
    cout << "Enter a sentence: ";
    getline(cin, sentence);

    stringstream ss(sentence);
    vector<string> words;
    string word;

    while (ss >> word) {
        words.push_back(word);
    }

    for (int i = words.size() - 1; i >= 0; i--) {
        cout << words[i];
        if (i != 0) cout << " ";
    }
    cout << endl;

    return 0;
}