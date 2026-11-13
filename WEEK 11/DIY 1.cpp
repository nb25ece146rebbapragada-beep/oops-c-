#include <iostream>
using namespace std;

template <typename T>
void swapVals(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
T findMax(T arr[], int n) {
    T maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    return maxVal;
}

int main() {
    // Test with int
    int a = 10, b = 20;
    cout << "Before swap (int): a = " << a << ", b = " << b << endl;
    swapVals(a, b);
    cout << "After swap (int):  a = " << a << ", b = " << b << endl;

    int intArr[] = {3, 7, 1, 9, 4};
    cout << "Max of int array: " << findMax(intArr, 5) << endl;

    cout << endl;

    // Test with double
    double x = 1.5, y = 2.75;
    cout << "Before swap (double): x = " << x << ", y = " << y << endl;
    swapVals(x, y);
    cout << "After swap (double):  x = " << x << ", y = " << y << endl;

    double dblArr[] = {2.5, 8.1, 3.3, 7.9};
    cout << "Max of double array: " << findMax(dblArr, 4) << endl;

    return 0;
}