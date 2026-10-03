#include <iostream>
using namespace std;

long long power(int base, int exp = 2) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int main() {
    cout << "power(5) = " << power(5) << endl;
    cout << "power(2, 10) = " << power(2, 10) << endl;
    return 0;
}