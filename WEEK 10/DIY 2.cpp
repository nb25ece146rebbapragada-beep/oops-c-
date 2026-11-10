#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream in("in.txt");
    if (!in) {
        cout << "Cannot open in.txt" << endl;
        return 1;
    }
    ofstream out("out.txt");

    string line;
    int n = 1;
    while (getline(in, line)) {
        out << n << ": " << line << "\n";
        n++;
    }

    in.close();
    out.close();
    cout << "Copied " << n - 1 << " lines to out.txt" << endl;
    return 0;
}