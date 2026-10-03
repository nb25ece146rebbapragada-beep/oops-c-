#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;
    int capacity;
    int topIndex;   // index of top element, -1 when empty

    void grow() {
        int newCap = capacity * 2;
        int* bigger = new int[newCap];
        for (int i = 0; i <= topIndex; i++)
            bigger[i] = arr[i];
        delete[] arr;
        arr = bigger;
        capacity = newCap;
    }

public:
    Stack(int cap = 2) : capacity(cap), topIndex(-1) {
        arr = new int[capacity];
    }

    // Disable copying to avoid double-delete of the buffer
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    ~Stack() {
        delete[] arr;
        cout << "Stack buffer released" << endl;
    }

    void push(int value) {
        if (topIndex + 1 == capacity)
            grow();
        arr[++topIndex] = value;
    }

    bool pop(int& value) {
        if (isEmpty()) return false;
        value = arr[topIndex--];
        return true;
    }

    bool isEmpty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }
};

int main() {
    Stack s;
    for (int i = 1; i <= 5; i++) {
        s.push(i * 10);
        cout << "Pushed " << i * 10 << endl;
    }

    int x;
    cout << "Popping:" << endl;
    while (s.pop(x))
        cout << x << endl;

    if (!s.pop(x))
        cout << "Stack is empty" << endl;

    return 0;
}