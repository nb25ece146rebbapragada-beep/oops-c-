#include <iostream>
#include <stdexcept>

class SafeArray {
private:
    int* arr;
    int size;

public:
    SafeArray(int s) : size(s) {
        arr = new int[size]{0}; // Initialize with zeros
    }

    ~SafeArray() {
        delete[] arr;
    }

    // Overload operator[] for modification/access
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Array index out of bounds exception!");
        }
        return arr[index];
    }

    // Overload operator[] for const objects (read-only)
    const int& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Array index out of bounds exception!");
        }
        return arr[index];
    }

    int getSize() const { return size; }
};

int main() {
    SafeArray myArr(5);

    try {
        // Valid operations
        myArr[0] = 10;
        myArr[4] = 50;
        std::cout << "Element at index 0: " << myArr[0] << std::endl;
        std::cout << "Element at index 4: " << myArr[4] << std::endl;

        // Triggering out-of-bounds error
        std::cout << "Attempting to access index 5..." << std::endl;
        myArr[5] = 100; 
    } 
    catch (const std::out_of_range& e) {
        std::cerr << "Caught Error: " << e.what() << std::endl;
    }

    return 0;
}
