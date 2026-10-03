#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    string a, b;
    cout << "Enter two words: ";
    cin >> a >> b;

    // Make comparison case-insensitive
    for (char &c : a) c = tolower(static_cast<unsigned char>(c));
    for (char &c : b) c = tolower(static_cast<unsigned char>(c));

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    if (a == b)
        cout << "The words are anagrams." << endl;
    else
        cout << "The words are NOT anagrams." << endl;

    return 0;
}