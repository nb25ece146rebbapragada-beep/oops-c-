#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream in("nums.txt");
    if (!in) {
        cout << "Cannot open nums.txt" << endl;
        return 1;
    }

    int x, count = 0, sum = 0, mn = 0, mx = 0;
    while (in >> x) {
        if (count == 0) {
            mn = mx = x;
        } else {
            if (x < mn) mn = x;
            if (x > mx) mx = x;
        }
        sum += x;
        count++;
    }
    in.close();

    if (count == 0) {
        cout << "File has no numbers" << endl;
        return 0;
    }

    cout << "Count: " << count << endl;
    cout << "Sum: " << sum << endl;
    cout << "Min: " << mn << endl;
    cout << "Max: " << mx << endl;
    return 0;
}