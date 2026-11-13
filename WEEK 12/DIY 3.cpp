#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6};

    // Product of all elements
    long long product = accumulate(nums.begin(), nums.end(), 1LL,
        [](long long acc, int x) {
            return acc * x;
        });

    // Sum of only the even elements
    int evenSum = accumulate(nums.begin(), nums.end(), 0,
        [](int acc, int x) {
            return (x % 2 == 0) ? acc + x : acc;
        });

    cout << "Elements: ";
    for (int x : nums) cout << x << " ";
    cout << endl;

    cout << "Product of all elements: " << product << endl;
    cout << "Sum of even elements: " << evenSum << endl;

    return 0;
}